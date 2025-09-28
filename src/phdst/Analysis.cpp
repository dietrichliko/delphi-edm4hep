// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: Implementation of the Analysis singleton class

#include <stdexcept>
#include <spdlog/spdlog.h>
#include <phdst/Analysis.hpp>
#include <phdst/functions.hpp>
#include <phdst/phlun.hpp>

namespace phdst {

// Initialize static member
Analysis* Analysis::instance_ = nullptr;

Analysis::Analysis() : max_event_(0) {
    // Ensure only one instance can exist
    if (instance_ != nullptr) {
        spdlog::error("Analysis instance already exists. Only one Analysis instance (base or derived) is allowed.");
        throw std::runtime_error("Analysis instance already exists. Only one Analysis instance (base or derived) is allowed.");
    }
    
    // Register this instance
    instance_ = this;
    spdlog::debug("Analysis instance created successfully");
}

Analysis::~Analysis() {
    // Clear the instance pointer when destroyed
    instance_ = nullptr;
    spdlog::debug("Analysis instance destroyed");
}

int Analysis::run(const std::string & options) {
    spdlog::info("Starting PHDST analysis with options: '{}'", options);
    // Initialize PHDST with the provided options
    int result = PHDST(options);
    spdlog::debug("PHDST completed with status: {}", result);
    return result;
}

void Analysis::setMaxEvent(int max_events) {
    max_event_ = max_events;
    if (max_events > 0) {
        spdlog::info("Maximum events limit set to: {}", max_events);
    } else {
        spdlog::info("Maximum events limit removed (unlimited processing)");
    }
}

void Analysis::setInput(const std::string &filepath) {
    input_files_.push_back(filepath);
    spdlog::debug("Added input file: '{}' (total files: {})", filepath, input_files_.size());
}

int Analysis::pilot_record() {
    // Check if we should limit the number of events
    if (max_event_ > 0) {
        int current_event = NEVENT();
        if (current_event >= max_event_) {
            // Stop processing - we've reached the maximum
            spdlog::info("Reached maximum event limit: {} >= {}, stopping processing", current_event, max_event_);
            return -3;
        }
        if (current_event % 1000 == 0) {
            spdlog::debug("Processing event {}/{}", current_event, max_event_);
        }
    }
    
    // Call the virtual user01() method
    return user01();
}

void Analysis::init() {
    spdlog::info("Initializing Analysis with {} input files", input_files_.size());
    
    // Process stored input files by calling PHPONE for each
    for (const auto& filepath : input_files_) {
        spdlog::debug("Processing input file: '{}'", filepath);
        std::string command = "FILE =" + filepath;
        int status = PHPONE(command);
        if (status != 0) {
            spdlog::error("PHPONE failed for file '{}' with status: {}", filepath, status);
            throw std::runtime_error("PHPONE failed for file: " + filepath + " (status: " + std::to_string(status) + ")");
        }
        spdlog::debug("Successfully processed input file: '{}'", filepath);
    }
    
    // Set LUNPDL to 0
    LUNPDL = 0;
    spdlog::debug("Set LUNPDL to 0");
    
    spdlog::debug("Calling user00() for custom initialization");
    // Call the virtual user00() method that can be overridden by derived classes
    user00();
    
    spdlog::info("Analysis initialization completed successfully");
}

// Default implementations of virtual methods
void Analysis::user00() {
    // Default implementation - can be overridden by derived classes
}

int Analysis::user01() {
    // Default implementation - can be overridden by derived classes
    return 0;
}

void Analysis::user02() {
    // Default implementation - can be overridden by derived classes
}

void Analysis::user99() {
    // Default implementation - can be overridden by derived classes
}

} // namespace phdst

// C interface for Fortran interoperability
// These functions provide C linkage to the Analysis singleton methods
// Note: Called by the framework, so Analysis instance is guaranteed to exist
extern "C" {

void user00_() {
    phdst::Analysis::getInstance()->init();
}

int user01_() {
    return phdst::Analysis::getInstance()->pilot_record();
}

void user02_() {
    phdst::Analysis::getInstance()->user02();
}

void user99_() {
    phdst::Analysis::getInstance()->user99();
}

} // extern "C"