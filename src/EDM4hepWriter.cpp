// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: Implementation of EDM4hep writer for DELPHI data conversion

#include <stdexcept>
#include <ctime>
#include <spdlog/spdlog.h>
#include <phdst/phdst.hpp>
#include <podio/Frame.h>
#include <podio/ROOTWriter.h>
#include <edm4hep/EventHeaderCollection.h>
#include <delphi_edm4hep/EventHeaderCollection.h>
#include <delphi_edm4hep/EventHeader.h>
#include <delphi_edm4hep/TimeStamp.h>
#include <EDM4hepWriter.hpp>


EDM4hepWriter::EDM4hepWriter() 
    : phdst::Analysis()
    , output_path_("output.edm4hep.root") {
    spdlog::info("EDM4hepWriter instance created");
}

EDM4hepWriter::~EDM4hepWriter() {
    spdlog::info("EDM4hepWriter destroyed");
}

void EDM4hepWriter::setOutput(const std::string& output_path) {
    output_path_ = output_path;
    spdlog::info("EDM4hep output file set to: {}", output_path_);
}

void EDM4hepWriter::user00() {
    spdlog::info("EDM4hepWriter::user00() - Initializing EDM4hep conversion");
    
    writer_ = std::make_unique<podio::ROOTWriter>(output_path_);

    spdlog::info("Output file: {}", output_path_);
}

int EDM4hepWriter::user01() {
    // For now, process all events
    // Future: Add event selection logic here
    spdlog::debug("EDM4hepWriter::user01() - Event selection");
    return 1; // Process this event
}

void EDM4hepWriter::user02() {
    spdlog::debug("EDM4hepWriter::user02() - Converting event {} to EDM4hep", phdst::NEVENT);
    startEvent();
    fillEventHeader();
    finishEvent();
}

void EDM4hepWriter::user99() {
    spdlog::info("EDM4hepWriter::user99() - Finalizing EDM4hep conversion");
    
    writer_->finish();
    writer_.reset();  // Delete the writer object and set pointer to null
    
    spdlog::info("EDM4hep conversion completed successfully");
}

void EDM4hepWriter::startEvent() {
    spdlog::debug("EDM4hepWriter::startEvent() - Starting event {}", phdst::IIIEVT);
    
    // Initialize collections for the new event
    event_header_collection_ = std::make_unique<edm4hep::EventHeaderCollection>();
    delphi_event_header_collection_ = std::make_unique<delphi::EventHeaderCollection>();
}

void EDM4hepWriter::finishEvent() {
    spdlog::debug("EDM4hepWriter::finishEvent() - Finalizing event {}", phdst::IIIEVT);

    // Put all collections into the eventFrame
    podio::Frame eventFrame;
    eventFrame.put(std::move(*event_header_collection_), "EventHeader");
    eventFrame.put(std::move(*delphi_event_header_collection_), "DelphiEventHeader");

    writer_->writeFrame(eventFrame, "events");

    event_header_collection_.reset();
    delphi_event_header_collection_.reset();
}

void EDM4hepWriter::fillEventHeader() {
    spdlog::debug("EDM4hepWriter::fillEventHeader() - Filling header for event {}", phdst::IIIEVT);
    
    // Fill standard EDM4hep event header
    auto eventHeader = event_header_collection_->create();
    eventHeader.setEventNumber(phdst::IIIEVT);
    eventHeader.setRunNumber(phdst::IIIRUN);
    eventHeader.setTimeStamp(event_timestamp());
    eventHeader.setWeight(1.0);
    
    // Fill DELPHI-specific event header
    auto delphiHeader = delphi_event_header_collection_->create();
    delphiHeader.setEventNumber(phdst::IIIEVT);
    delphiHeader.setRunNumber(phdst::IIIRUN);
    delphiHeader.setFileNumber(phdst::IIFILE);
    delphiHeader.setFillNumber(phdst::IIFILL);
    delphiHeader.setExperimentNumber(phdst::IIIEXP);
    delphiHeader.setDelphiDate(phdst::IIIDAT);
    delphiHeader.setDelphiTime(phdst::IIITIM);
    delphiHeader.setWeight(1.0);
    
    // Set the timestamp
    delphi::TimeStamp timestamp;
    timestamp.setUnixTime(static_cast<std::uint64_t>(event_timestamp()));
    delphiHeader.setTimeStamp(timestamp);
    
    // Set beam spot (placeholder values for now)
    delphi::Vector3f beamSpot;
    beamSpot.setX(0.0f);
    beamSpot.setY(0.0f);
    beamSpot.setZ(0.0f);
    delphiHeader.setBeamSpot(beamSpot);
    
    // Set metadata strings (empty for now, can be filled from PHDST data)
    delphiHeader.setTriggerInfo("");
    delphiHeader.setDataQuality("");
}

int EDM4hepWriter::event_timestamp() {
    // Convert DELPHI date/time format (YYMMDD/HHMMSS) to Unix timestamp
    int date = phdst::IIIDAT;
    int time = phdst::IIITIM;
    
    // Extract components and convert 2-digit year (89-99 -> 1989-1999, 00-20 -> 2000-2020)
    int year = (date / 10000 >= 89) ? 1900 + date / 10000 : 2000 + date / 10000;
    
    std::tm tm_struct = {
        .tm_sec = time % 100,
        .tm_min = (time / 100) % 100,
        .tm_hour = time / 10000,
        .tm_mday = date % 100,
        .tm_mon = (date / 100) % 100 - 1,  // months since January (0-11)
        .tm_year = year - 1900,            // years since 1900
        .tm_isdst = 0                      // assume no DST
    };
    
    std::time_t timestamp = std::mktime(&tm_struct);
    
    if (timestamp == -1) {
        spdlog::error("Failed to convert date/time to timestamp: date={}, time={}", date, time);
        return 0;
    }
    
    return static_cast<int>(timestamp);
}