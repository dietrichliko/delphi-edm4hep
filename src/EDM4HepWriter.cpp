#include <iostream>
#include <string>
#include "spdlog/spdlog.h"

#include "phdst.hpp"
#include "skelana.hpp"
#include "EDM4HepWriter.hpp"

namespace sk = skelana;

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

void EDM4HepWriter::user02() {
    std::cout << "EDM4HepWriter::user02() called" << std::endl;
    sk::PSBEG();
}

void EDM4HepWriter::user99() {
    std::cout << "EDM4HepWriter::user99() called" << std::endl;
    // Call the Fortran function for user99
}

void EDM4HepWriter::addPDLInput(const std::string& line) {
    spdlog::info("Adding PDL input line: {}", line);
    pdl_input_lines_.push_back(line);
}

void EDM4HepWriter::setOutput(const std::string& output) {
    spdlog::info("Setting output file to {} (ignored)", output);
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