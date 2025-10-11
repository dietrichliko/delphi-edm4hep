// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: Implementation of EDM4hep writer for DELPHI data conversion

#include <stdexcept>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <TMath.h>
#include <spdlog/spdlog.h>
#include <phdst/phdst.hpp>
#include <podio/Frame.h>
#include <podio/ROOTWriter.h>
#include <edm4hep/EventHeaderCollection.h>
#include <edm4hep/MutableVertex.h>
#include <edm4hep/VertexCollection.h>
#include <edm4hep/ReconstructedParticleCollection.h>
#include <edm4hep/MCParticleCollection.h>
#include <edm4hep/MCRecoParticleAssociationCollection.h>
#include <edm4delphi/EventHeaderCollection.h>
#include <edm4delphi/RunHeaderCollection.h>
#include <edm4delphi/BTaggingCollection.h>
#include <dstana/dstana.hpp>
#include <mamoth/mamoth.hpp>
#include <edm4hep_writer.hpp>


EDM4hepWriter::EDM4hepWriter() 
    : phdst::Analysis() {
    
    spdlog::info("EDM4hepWriter instance created");
}

EDM4hepWriter::~EDM4hepWriter() {
    spdlog::info("EDM4hepWriter destroyed");
}

void EDM4hepWriter::setOutput(const std::string& output_path) {
    output_path_ = output_path;
    spdlog::info("EDM4hep output file set to: {}", output_path_);
}

void EDM4hepWriter::setFixSecondaryHadronicInteractions(bool enable) {
    fix_secondary_hadronic_interactions_ = enable;
    spdlog::info("Secondary hadronic interaction fixing {}", enable ? "enabled" : "disabled");
}

bool EDM4hepWriter::is_mc() const {
    return phdst::IIIRUN < 0;
}



void EDM4hepWriter::user00() {
    spdlog::info("EDM4hepWriter::user00() - Initializing EDM4hep conversion");
    
    writer_ = std::make_unique<podio::ROOTWriter>(output_path_);
    spdlog::info("Output file: {}", output_path_);

    // Initialize zebra pointer registry
    phdst::ZebraPointer::initialize();
}

int EDM4hepWriter::user01() {
    // Call the base class method first
    int base_result = phdst::Analysis::user01();
    
    // If base class says to skip/stop, respect that
    if (base_result <= 0) {
        return base_result;
    }
    
    // Add our own event selection logic here
    spdlog::debug("EDM4hepWriter::user01() - Event selection");
    
    // For now, process all events that passed base class selection
    // Future: Add additional event selection logic here
    return 1; // Process this event
}

void EDM4hepWriter::user02() {
    spdlog::debug("EDM4hepWriter::user02() - Converting event {} to EDM4hep", phdst::NEVENT);
    if (phdst::LDTOP <= 0) {
        spdlog::warn("LDTOP is non-positive ({}), skipping event {}", phdst::LDTOP, phdst::NEVENT);
        return; // Skip event if no valid data
    }

    // Add missing blocklets
    if (fix_secondary_hadronic_interactions_) {
        fixSecondaryHadronicInteractions();
    }

    // Now the real conversion is starting.
    startEvent();
    fillEventHeader();
    fillVertices();
    fillRecoParticles();
    if (is_mc()) {
        fillMCParticles();
        fillMCRecoParticleAssociations();
    }
    fillBTagging();

    finishEvent();
    phdst::ZebraPointer::reset();
}

void EDM4hepWriter::user99() {
    spdlog::info("EDM4hepWriter::user99() - Finalizing EDM4hep conversion");

    if (phdst::NEVENT > 0) {
        finishRun();
    }

    writer_->finish();
    writer_.reset();  // Delete the writer object and set pointer to null
    
    spdlog::info("EDM4hep conversion completed successfully");
}

void EDM4hepWriter::startEvent() {
    spdlog::debug("EDM4hepWriter::startEvent() - Starting event {}", phdst::IIIEVT);

    // Get physics parameters for this event
    obtainCenterOfMassEnergy();
    obtainMagneticField();

    // Check if we need to write the previous run header and start a new one
    spdlog::debug("Run {}, File {}", current_run_, current_file_);
    spdlog::debug("New Run {}, New File {}", phdst::IIIRUN, phdst::IIFILE);
    if ((current_run_ != phdst::IIIRUN) || (current_file_ != phdst::IIFILE)) {
        if (phdst::NEVENT > 0) {
            finishRun();
        }
        startRun();
    } else {


        // Same run and file, just increment event count and check for consistency
        run_event_count_++; 
    }
    
    // Initialize collections for the new event
    event_header_collection_ = std::make_unique<edm4hep::EventHeaderCollection>();
    delphi_event_header_collection_ = std::make_unique<edm4delphi::EventHeaderCollection>();
    vertex_collection_ = std::make_unique<edm4hep::VertexCollection>();
    reco_particle_collection_ = std::make_unique<edm4hep::ReconstructedParticleCollection>();
    if (is_mc()) {
        mc_particle_collection_ = std::make_unique<edm4hep::MCParticleCollection>();
        mc_reco_particle_association_collection_ = std::make_unique<edm4hep::MCRecoParticleAssociationCollection>();
    }
    
}

void EDM4hepWriter::finishEvent() {
    spdlog::debug("EDM4hepWriter::finishEvent() - Finalizing event {}", phdst::IIIEVT);


    // Put all collections into the eventFrame
    podio::Frame eventFrame;
    eventFrame.put(std::move(*event_header_collection_), "EventHeader");
    eventFrame.put(std::move(*delphi_event_header_collection_), "DelphiEventHeader");
    eventFrame.put(std::move(*vertex_collection_), "Vertices");
    eventFrame.put(std::move(*reco_particle_collection_), "ReconstructedParticles");
    if (is_mc()) {
        eventFrame.put(std::move(*mc_particle_collection_), "MCParticles");
        eventFrame.put(std::move(*mc_reco_particle_association_collection_), "MCRecoParticleAssociations");
    }

    writer_->writeFrame(eventFrame, "events");

    event_header_collection_.reset();
    delphi_event_header_collection_.reset();
    vertex_collection_.reset();
    reco_particle_collection_.reset();
    mc_particle_collection_.reset();
    mc_reco_particle_association_collection_.reset();
    vertex_ptrs_.clear();
    reco_particle_ptrs_.clear();
    zebra_to_vertex_index_.clear();
    zebra_to_reco_particle_index_.clear();
}

void EDM4hepWriter::fillEventHeader() {
    spdlog::debug("EDM4hepWriter::fillEventHeader() - Filling header for event {}", phdst::IIIEVT);

    // Fill DELPHI-specific event header
    auto delphiHeader = delphi_event_header_collection_->create();
    delphiHeader.setEventNumber(phdst::IIIEVT);
    delphiHeader.setRunNumber(phdst::IIIRUN);
    delphiHeader.setFileNumber(phdst::IIFILE);
    delphiHeader.setDateTime(phdst::IIIDAT, phdst::IIITIM);
    delphiHeader.setMagneticField(magnetic_field_);

    // get various event properties from DELPHI DST
    delphiHeader.setNrChargedTracks(0);
    delphiHeader.setNrChargedTracksT4(0);
    delphiHeader.setNrNeutralTracks(0);
    delphiHeader.setTotChargedEnergy(0); 
    delphiHeader.setTotEMNeutralEnergy(0);
    delphiHeader.setTotHadNeutralEnergy(0);
    delphiHeader.setHadronTagT4(true);
    delphiHeader.setProbForTracksWithNegativeIP(edm4hep::Vector3f{0.0f, 0.0f, 0.0f});
    delphiHeader.setProbForTracksWithPositiveIP(edm4hep::Vector3f{0.0f, 0.0f, 0.0f});
    delphiHeader.setThrustAxis(edm4hep::Vector3f{0.0f, 0.0f, 0.0f});


    // Fill standard EDM4hep event header
    auto eventHeader = event_header_collection_->create();
    eventHeader.setEventNumber(phdst::IIIEVT);
    eventHeader.setRunNumber(phdst::IIIRUN);
    eventHeader.setTimeStamp(delphiHeader.getTimeStamp());
    eventHeader.setWeight(1.0);
    

}

void EDM4hepWriter::fillVertices() {
    spdlog::debug("EDM4hepWriter::fillVertices() - Processing DELPHI vertex data for event {}", phdst::IIIEVT);

    spdlog::trace("LDTOP = {}", phdst::LDTOP);
    phdst::ZebraPointer lpv = phdst::ZebraPointer::create(phdst::LDTOP-1); // Pointer to vertex data structure
    while (lpv.is_valid()) {
        spdlog::trace("Processing vertex with ZebraPointer link {}", lpv.get_link());
        
        int status_bits = lpv.int_at(0);
        spdlog::trace("vertex status bits: 0x{:X}", status_bits);

        // Skip dummy vertices (bit 0 set)
        if (status_bits & 0x1) {
            spdlog::trace("Skipping dummy vertex (bit 0 set)");
            lpv = lpv.ptr_at(0);
            continue;
        }

        auto vtx = vertex_collection_->create();
        
        // Store ZebraPointer and create mapping to collection index
        size_t vertex_index = vertex_ptrs_.size();
        vertex_ptrs_.push_back(lpv);
        zebra_to_vertex_index_[lpv] = vertex_index;
        
        vtx.setPrimary( status_bits & 0x2 ? 0 : 1 ); // Bit 1 indicates secondary vertex
        vtx.setChi2(lpv.float_at(8));
        vtx.setProbability(TMath::Prob(lpv.float_at(8), lpv.int_at(3)));
        vtx.setPosition(edm4hep::Vector3f{lpv.float_at(5), lpv.float_at(6), lpv.float_at(7)});
        vtx.setCovMatrix(std::array<float, 6>{lpv.float_at(9), lpv.float_at(10), lpv.float_at(11), lpv.float_at(12), lpv.float_at(13), lpv.float_at(14)});


        lpv = lpv.ptr_at(0);

    }
    
    spdlog::trace("Vertex processing completed - {} vertices in map", vertex_map_.size());
}

void EDM4hepWriter::obtainCenterOfMassEnergy() {
    int idana = phdst::IPHPIC("DANA");
    float ecmas;
    
    if (idana <= 0) {
        // No DANA bank found, use default Z boson mass
        ecmas = 91.250f;
        spdlog::debug("No DANA bank found (IDANA={}), using default CM energy: {} GeV", idana, ecmas);
    } else {
        // Read center-of-mass energy from DANA bank (stored in MeV, convert to GeV)
        int ecmas_mev = phdst::IPILOT(idana + 13);
        ecmas = static_cast<float>(ecmas_mev) / 1000.0f;
        spdlog::debug("Read CM energy from DANA bank: {} MeV = {} GeV (IDANA={})", ecmas_mev, ecmas, idana);
    }
    
    // Check for consistency within the run
    if (center_of_mass_energy_ > 0.0f) {
        if (std::abs(center_of_mass_energy_ - ecmas) > 0.005f) {  // 5 MeV tolerance
            spdlog::warn("Center-of-mass energy changed during run {}: {} GeV -> {} GeV", 
                        phdst::IIIRUN, center_of_mass_energy_, ecmas);
        }
    } else {
        center_of_mass_energy_ = ecmas;
    }
}

void EDM4hepWriter::obtainMagneticField() {
    float bgevcm;
    dstana::BPILOT(magnetic_field_, bgevcm);
}

void EDM4hepWriter::startRun() {
    spdlog::info("EDM4hepWriter::startRun() - Starting new run {}, file {}", 
                 phdst::IIIRUN, phdst::IIFILE);
    
    current_run_ = phdst::IIIRUN;
    current_file_ = phdst::IIFILE;
    run_event_count_ = 0;
    
    // Reset physics parameters for new run (0 = unset)
    center_of_mass_energy_ = 0.0f;

    spdlog::debug("Run header initialized for run {}, file {}", current_run_, current_file_);
}

void EDM4hepWriter::finishRun() {

    
    spdlog::debug("EDM4hepWriter::finishRun() - Writing run header for run {}, file {} ({} events)", 
                 current_run_, current_file_, run_event_count_);
    

    // Create new run header collection
    edm4delphi::RunHeaderCollection  run_header_collection;
    
    // Create and fill the run header
    auto runHeader = run_header_collection.create();
    runHeader.setExperimentNumber(phdst::IIIEXP);
    runHeader.setRunNumber(phdst::IIIRUN);
    runHeader.setFileNumber(phdst::IIFILE);
    runHeader.setFillNumber(phdst::IIFILL); 
    runHeader.setEventCount(0); // Will be updated later
    runHeader.setCenterOfMassEnergy(center_of_mass_energy_);
    runHeader.setProcessingTag(dstana::DSTQID());                 
    runHeader.setEventCount(run_event_count_);

    // Write run header to a dedicated frame
    podio::Frame runFrame;
    runFrame.put(std::move(run_header_collection), "RunHeader");
    writer_->writeFrame(runFrame, "runs");
    
    spdlog::debug("Run header written for run {}, file {}", current_run_, current_file_);
}


void EDM4hepWriter::fillRecoParticles() {
    spdlog::debug("EDM4hepWriter::fillRecoParticles() - Processing DELPHI reconstructed particle data for event {}", phdst::IIIEVT);
    
    // TODO: Implement reconstructed particle processing
    // This will involve reading DELPHI track and cluster data
    // and converting them to EDM4hep ReconstructedParticle objects
    
    spdlog::trace("Reconstructed particle processing completed");
}

void EDM4hepWriter::fillMCParticles() {
    spdlog::debug("EDM4hepWriter::fillMCParticles() - Processing DELPHI Monte Carlo particle data for event {}", phdst::IIIEVT);
    
    if (!is_mc()) {
        spdlog::debug("Not Monte Carlo data, skipping MC particle processing");
        return;
    }
    
    // TODO: Implement Monte Carlo particle processing
    // This will involve reading DELPHI MC truth data
    // and converting them to EDM4hep MCParticle objects
    
    spdlog::trace("Monte Carlo particle processing completed");
}

void EDM4hepWriter::fillMCRecoParticleAssociations() {
    spdlog::debug("EDM4hepWriter::fillMCRecoParticleAssociations() - Creating MC-Reco associations for event {}", phdst::IIIEVT);
    
    if (!is_mc()) {
        spdlog::debug("Not Monte Carlo data, skipping MC-Reco associations");
        return;
    }
    
    // TODO: Implement MC-Reco particle associations
    // This will involve linking MC particles to reconstructed particles
    // based on DELPHI tracking and simulation information
    
    spdlog::trace("MC-Reco particle association processing completed");
}

void EDM4hepWriter::fillBTagging() {
    spdlog::debug("EDM4hepWriter::fillBTagging() - Processing BTagging information for event {}", phdst::IIIEVT);

    // TODO: Implement BTagging information processing
    // This will involve reading DELPHI BTagging data structures
    // and converting them to EDM4hep BTagging objects

    spdlog::trace("BTagging processing completed");
}

void EDM4hepWriter::fixSecondaryHadronicInteractions() {
    spdlog::debug("EDM4hepWriter::fixSecondaryHadronicInteractions() - Fixing secondary hadronic interactions for event {}", phdst::IIIEVT);

    // Traverse the ZEBRA data structure to find and fix secondary hadronic interaction blocklets
    // Secondary hadronic interaction blocklets are identified by specific patterns in their data
    // Here we look for blocklets where 7 bits starting at bit position 18 equal 120 (0x78)
    // and a TRAC module (8) will be added by MAKEMOD8.
    // Due to Zebra, LPA pointer will change if a module is added. As the structure stays consistent,
    // the loop can continue safely. 
    std::uint32_t LPV = phdst::LQ(phdst::LDTOP-1);
    while (LPV > 0) {
        std::uint32_t LPA = phdst::LQ(LPV - 1);
        while (LPA > 0) {
            // Check if 7 bits starting at bit position 18 equal 120 (0x78 << 18 = 0x1E00000)
            std::uint32_t word = static_cast<std::uint32_t>(phdst::IQ(LPA+3));
            if ((word & 0x1FC0000U) == 0x1E00000U) {  // mask: 0x7F << 18, value: 120 << 18
                spdlog::trace("Found secondary hadronic interaction blocklet at LPA = {}, applying MAKEMOD8", LPA);
                int ierr = mamoth::MAKEMOD8(LPA, false);  // LPA may be modified by MAKEMOD8
                if (ierr != 0) {
                    spdlog::error("MAKEMOD8 failed for LPA = {} with error code {}", LPA, ierr);
                }
                spdlog::trace("After MAKEMOD8: LPA = {}", LPA);
            }
            // Use the potentially modified LPA value to get the next link
            LPA = phdst::LQ(LPA);
        }
        LPV = phdst::LQ(LPV);
    }
    spdlog::trace("Secondary hadronic interaction corrections completed");
}

int EDM4hepWriter::findVertexIndex(const phdst::ZebraPointer& zebra_ptr) const {
    auto it = zebra_to_vertex_index_.find(zebra_ptr);
    if (it != zebra_to_vertex_index_.end()) {
        return static_cast<int>(it->second);
    }
    return -1; // Not found
}