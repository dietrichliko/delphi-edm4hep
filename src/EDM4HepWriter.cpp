#include <iostream>
#include <string>
#include "spdlog/spdlog.h"

#include "phdst.hpp"
#include "skelana.hpp"
#include "EDM4HepWriter.hpp"

#include "TMath.h"

#include "edm4hep/EventHeaderCollection.h"
#include "edm4hep/ReconstructedParticleCollection.h"
#include "edm4hep/MCParticleCollection.h"
#include "edm4hep/VertexCollection.h"
#include "edm4hep/MCRecoParticleAssociationCollection.h"
#include "podio/Frame.h"

namespace sk = skelana;

std::int64_t create_timestamp(int date, int time) {
    int year  = date / 10000;
    int month = (date / 100) % 100;
    int day   = date % 100;

    int hour   = time / 10000;
    int minute = (time / 100) % 100;
    int second = time % 100;

    std::tm t = {};
    t.tm_year = year - 1900; // years since 1900
    t.tm_mon  = month - 1;   // months since January [0–11]
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min  = minute;
    t.tm_sec  = second;

    std::time_t tt = timegm(&t);      // POSIX

    // Convert to nanoseconds
    return static_cast<std::int64_t>(tt) * 1000000000LL;
}

bool EDM4HepWriter::is_mc() const {
    return phdst::IIIRUN < 0;
}   

EDM4HepWriter& EDM4HepWriter::instance() {
    static EDM4HepWriter instance; // Singleton instance
    return instance;
}   

void EDM4HepWriter::user00() {
    // spdlog::info("EDM4HepWriter::user00() called");

    // if PDL input lines are provided, do not read PDLINPUT
    if (!pdl_input_lines_.empty()) {
        spdlog::info("Setting LUNPDL to 0, PDLINPUT is ignored.");
        phdst::LUNPDL = 0;
    }
    for (const auto& line : pdl_input_lines_) {
        int flag = phdst::PHPONE(line);
        if (flag != 0) {
            spdlog::error("Error processing PDL line: {}", line);
        }   
    }

    // Supress floating point errors
    phdst::PHSET("FPE", 0);
    // Skelana initialization
    sk::PSINI();

    // Create podio writer
    writer_ = std::make_unique<podio::ROOTWriter>(output_file_);
}

int EDM4HepWriter::user01() {
    spdlog::info("EDM4HepWriter::user01() called");

    // skip record if not DST or no pilot
    if (phdst::NPILOT <= 0 or phdst::PHRTY() != "DST") {
        return 0; 
    }

    // stop processing if max events reached
    if (max_events_ > 0 && phdst::NEVENT > max_events_) {
        return -3; // Request to stop processing
    }
    return 1;
}

void EDM4HepWriter::fillEventFrame(podio::Frame& eventFrame) {


    auto event_header_coll = edm4hep::EventHeaderCollection();
    auto rec_vertex_coll = edm4hep::VertexCollection();
    auto rec_particle_coll = edm4hep::ReconstructedParticleCollection();
    auto sim_particle_coll = edm4hep::MCParticleCollection();
    auto rec_sim_particle_assoc_coll = edm4hep::MCRecoParticleAssociationCollection();

    // Make one header object
    auto event_header = event_header_coll.create();
    event_header.setEventNumber(phdst::IIIEVT);
    event_header.setRunNumber(phdst::IIIRUN);
    event_header.setTimeStamp(create_timestamp(phdst::IIIDAT, phdst::IIITIM));    


    // Fill reconstructed particles

    for( int i = 1; i <= sk::NVECP; ++i ) {
        auto particle = rec_particle_coll.create();
        // particle.setType(sk::IVECP(8,i)); // TODO: The head as a member PDG code
        particle.setEnergy(sk::VECP(4,i));
        // simply use VECP for momentum
        // TODO: Momentum, Reference point and cov matrix could be newly calculated
        // requires diffenet calulations according to particle type
        particle.setMomentum({sk::VECP(1,i), sk::VECP(2,i), sk::VECP(3,i)});
        // particle.setReferencePoint({sk::VECX(1,i), sk::VECX(2,i), sk::VECX(3,i)});
        // particle.covMatrix(); // not available
        particle.setCharge(sk::VECP(7,i));
        particle.setMass(sk::VECP(5,i));
        // particle.setGoodnessOfPID(0); // TODO: pid not yet understood
    }

    // Fill reconstructed vertices

    for( int i = 1; i <= sk::NVTX; ++i )
    {
        if ( sk::KVTX(17,i) & 0x1 ) continue; // skip dummy vertex
        auto vertex = rec_vertex_coll.create();
        vertex.setPrimary(sk::KVTX(0,i) == 0);
        vertex.setChi2(sk::QVTX(9,i));
        vertex.setProbability(TMath::Prob(sk::QVTX(9,i), sk::KVTX(4,i)));
        vertex.setPosition({sk::QVTX(6,i), sk::QVTX(7,i), sk::QVTX(8,i)});
        vertex.setCovMatrix(std::array<float, 6>{
                                sk::QVTX(10,i), sk::QVTX(11,i), sk::QVTX(12,i),
                                sk::QVTX(11,i), sk::QVTX(13,i), sk::QVTX(14,i)
                            });
        // Outgoing particles
        for (int i = 0; i < sk::KVTX(3,i); ++i) {
            int ip = sk::KVTX(1,i) + i - 1;
            auto particle = rec_particle_coll.at(ip);
            particle.setStartVertex(vertex);
        }
        // incoming particles
        if ( sk::KVTX(2,i) >  0 ) {
            int ip = sk::KVTX(2,i) - 1;
            auto particle = rec_particle_coll.at(ip);
            vertex.setAssociatedParticle(particle);
        }
    }


    if ( is_mc() ) {
        // Fill simulated particles
        for(int i = 1; i <= sk::NVECMC; ++i ){
            int ip = sk::MTRACK+i-1;
            auto particle = sim_particle_coll.create();
            particle.setPDG(sk::IVECP(8,ip));
            particle.setCharge(sk::IVECP(7,ip));
            particle.setMass(sk::VECP(5,ip));
            particle.setMomentum({sk::VECP(1,ip), sk::VECP(2,ip), sk::VECP(3,ip)});
            if (sk::ISTVX(1,i) > 0) {
                int iv = sk::ISTVX(1,i) + sk::NVTXMX;
                particle.setVertex({sk::QVTX(6, iv), sk::QVTX(7, iv), sk::QVTX(8, iv)});
            }
            if (sk::ISTVX(2,i) > 0) {
                int iv = sk::ISTVX(2,i) + sk::NVTXMX;
                particle.setEndpoint({sk::QVTX(6, iv), sk::QVTX(7, iv), sk::QVTX(8, iv)});
            }
            if (sk::ISTPA(i) > 0) {
               auto assoc = rec_sim_particle_assoc_coll.create();
               int ip_rec = sk::ISTPA(i) - 1;
               assoc.setRec(rec_particle_coll.at(ip_rec));
               assoc.setSim(particle); 
            }
        }
    }
    eventFrame.put(std::move(event_header_coll), "EventHeader");
    eventFrame.put(std::move(rec_vertex_coll), "ReconstuctedVertices");
    eventFrame.put(std::move(rec_particle_coll), "ReconstructedParticles");
    if ( is_mc() ) {
        eventFrame.put(std::move(sim_particle_coll), "SimulatedParticles");
        eventFrame.put(std::move(rec_sim_particle_assoc_coll), "RecoSimParticleAssociations");
    }
    eventFrame.putParameter("FILE_NUMBER", phdst::IIFILE);
    eventFrame.putParameter("EBEAM", sk::EBEAM);
    eventFrame.putParameter("BMAG", sk::BMAG);
}

void EDM4HepWriter::user02() {
    std::cout << "EDM4HepWriter::user02() called" << std::endl;
    sk::PSBEG();

    podio::Frame eventFrame;
    fillEventFrame(eventFrame);
    writer_->writeFrame(eventFrame, "events");

}

void EDM4HepWriter::user99() {
    std::cout << "EDM4HepWriter::user99() called" << std::endl;
    // Call the Fortran function for user99
    writer_->finish();
    writer_.reset();
}

void EDM4HepWriter::addPDLInput(const std::string& line) {
    spdlog::info("Adding PDL input line: {}", line);
    pdl_input_lines_.push_back(line);
}

void EDM4HepWriter::setOutput(const std::string& output) {
    spdlog::info("Setting output file to {} (ignored)", output);
    output_file_ = output;
}

void EDM4HepWriter::setMaxEvents(int maxEvents) {
    spdlog::info("Setting max events to {}", maxEvents);
    max_events_ = maxEvents;
}

void EDM4HepWriter::setSkelanaFlag(const std::string& options, const int value) {
    spdlog::info("Setting skelana flag for {} to {}", options, value);
}

int EDM4HepWriter::runAnalysis(const std::string& options) {
    // Call the Fortran function with the provided options
    return phdst::PHDST(options);
}

extern "C" void user00_() {
    EDM4HepWriter::instance().user00();
}

extern "C" void user01_(int * need) {
    *need = EDM4HepWriter::instance().user01();
}

extern "C" void user02_() {
    EDM4HepWriter::instance().user02();
}

extern "C" void user99_() {
    EDM4HepWriter::instance().user99();
}
