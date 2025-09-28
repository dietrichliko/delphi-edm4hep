// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: Main program for PHDST Analysis with command-line interface

#include <iostream>
#include <vector>
#include <memory>
#include <argparse/argparse.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <phdst/Analysis.hpp>

// ANSI color codes for enhanced output
namespace colors {
    const std::string reset = "\033[0m";
    const std::string red = "\033[31m";
    const std::string green = "\033[32m";
    const std::string yellow = "\033[33m";
    const std::string blue = "\033[34m";
    const std::string magenta = "\033[35m";
    const std::string cyan = "\033[36m";
    const std::string bold = "\033[1m";
}

/**
 * @brief Example Analysis implementation
 * 
 * This class demonstrates how to derive from phdst::Analysis and implement
 * custom analysis logic while leveraging the framework's initialization
 * and event processing capabilities.
 */
class ExampleAnalysis : public phdst::Analysis {
public:
    ExampleAnalysis() : Analysis() {
        spdlog::debug("ExampleAnalysis instance created");
    }
    
    void user00() override {
        spdlog::info("ExampleAnalysis::user00() - Custom initialization");
        // Custom initialization code would go here
        // e.g., book histograms, initialize counters, etc.
        event_count_ = 0;
        spdlog::info("Analysis initialization completed");
    }
    
    int user01() override {
        // This is called for each pilot record
        // Return 1 to read the event, 0 to skip, -3 to stop
        spdlog::debug("ExampleAnalysis::user01() - Pilot record processing");
        return 1; // Process this event
    }
    
    void user02() override {
        // This is called for each event after it's read
        event_count_++;
        if (event_count_ % 100 == 0) {
            spdlog::info("Processed {} events", event_count_);
        }
        spdlog::debug("ExampleAnalysis::user02() - Event {} processing", event_count_);
        
        // Custom event processing code would go here
        // e.g., analyze particles, fill histograms, etc.
    }
    
    void user99() override {
        spdlog::info("ExampleAnalysis::user99() - Finalization");
        spdlog::info("Total events processed: {}", event_count_);
        // Custom finalization code would go here
        // e.g., write histograms, print summary statistics, etc.
    }
    
private:
    int event_count_ = 0;
};

/**
 * @brief Configure spdlog for colored, single-threaded logging
 */
void setupLogging(const std::string& log_level) {
    // Create colored console logger for single-threaded use
    auto console = spdlog::stdout_color_st("console");
    spdlog::set_default_logger(console);
    
    // Set colored pattern
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
    
    // Set log level based on command line argument
    if (log_level == "trace") {
        spdlog::set_level(spdlog::level::trace);
    } else if (log_level == "debug") {
        spdlog::set_level(spdlog::level::debug);
    } else if (log_level == "info") {
        spdlog::set_level(spdlog::level::info);
    } else if (log_level == "warn") {
        spdlog::set_level(spdlog::level::warn);
    } else if (log_level == "error") {
        spdlog::set_level(spdlog::level::err);
    } else if (log_level == "critical") {
        spdlog::set_level(spdlog::level::critical);
    } else {
        spdlog::warn("Unknown log level '{}', using 'info'", log_level);
        spdlog::set_level(spdlog::level::info);
    }
    
    spdlog::info("Logging initialized with level: {}", log_level);
}

int main(int argc, char* argv[]) {
    try {
        // Configure argparse with colors
        argparse::ArgumentParser program("phdst_analysis", "1.0.0");
        
        // Customize program description with colors
        program.add_description(colors::bold + colors::cyan + 
                               "DELPHI-EDM4hep PHDST Analysis Program" + colors::reset + "\n" +
                               colors::green + 
                               "Process DELPHI DST files using the PHDST framework" + 
                               colors::reset);
        
        // Add command line arguments
        program.add_argument("input_files")
            .help(colors::yellow + "Input DST files to process (optional, uses PDLINPUT if not specified)" + colors::reset)
            .nargs(argparse::nargs_pattern::any)
            .metavar("FILE");
        
        program.add_argument("--max-events", "-n")
            .help(colors::yellow + "Maximum number of events to process" + colors::reset + 
                  " (0 = unlimited)")
            .default_value(0)
            .scan<'i', int>()
            .metavar("N");
        
        program.add_argument("--log-level", "-l")
            .help(colors::yellow + "Set log level" + colors::reset + 
                  " (trace, debug, info, warn, error, critical)")
            .default_value(std::string("info"))
            .metavar("LEVEL");
        
        program.add_argument("--verbose", "-v")
            .help(colors::yellow + "Enable verbose logging (sets log level to debug)" + colors::reset)
            .flag();
        
        // Parse command line arguments
        try {
            program.parse_args(argc, argv);
        } catch (const std::exception& err) {
            std::cerr << colors::red << colors::bold << "Error: " << colors::reset 
                      << colors::red << err.what() << colors::reset << std::endl;
            std::cerr << std::endl;
            std::cerr << program;
            return 1;
        }
        
        // Determine log level
        std::string log_level = program.get<std::string>("--log-level");
        if (program.get<bool>("--verbose")) {
            log_level = "debug";
        }
        
        // Initialize logging
        setupLogging(log_level);
        
        // Get parsed arguments
        auto input_files = program.get<std::vector<std::string>>("input_files");
        int max_events = program.get<int>("--max-events");
        
        // Log configuration
        spdlog::info("DELPHI-EDM4hep PHDST Analysis Starting");
        spdlog::info("Configuration:");
        
        if (input_files.empty()) {
            spdlog::info("  Input files: Using PDLINPUT file");
        } else {
            spdlog::info("  Input files: {} files", input_files.size());
            for (size_t i = 0; i < input_files.size(); ++i) {
                spdlog::info("    {}: {}", i + 1, input_files[i]);
            }
        }
        
        spdlog::info("  Max events:  {}", max_events == 0 ? "unlimited" : std::to_string(max_events));
        spdlog::info("  Log level:   {}", log_level);
        
        // Create analysis instance
        spdlog::info("Creating analysis instance");
        auto analysis = std::make_unique<ExampleAnalysis>();
        
        // Configure analysis
        if (max_events > 0) {
            analysis->setMaxEvent(max_events);
        }
        
        // Set input files if provided via command line
        if (!input_files.empty()) {
            for (const auto& file : input_files) {
                analysis->setInput(file);
            }
        } else {
            spdlog::info("No input files specified - using PDLINPUT file for input configuration");
        }
        
        // Run analysis
        spdlog::info("Starting PHDST analysis execution");
        int status = analysis->run();
        
        if (status == 0) {
            spdlog::info("Analysis completed successfully");
        } else {
            spdlog::error("Analysis completed with status: {}", status);
            return status;
        }
        
        // Analysis object will be destroyed here, calling user99()
        spdlog::info("DELPHI-EDM4hep PHDST Analysis Completed");
        
        return 0;
        
    } catch (const std::exception& e) {
        if (spdlog::default_logger()) {
            spdlog::critical("Fatal error: {}", e.what());
        } else {
            std::cerr << colors::red << colors::bold << "Fatal error: " 
                      << colors::reset << colors::red << e.what() << colors::reset << std::endl;
        }
        return 1;
    } catch (...) {
        if (spdlog::default_logger()) {
            spdlog::critical("Unknown fatal error occurred");
        } else {
            std::cerr << colors::red << colors::bold << "Unknown fatal error occurred" 
                      << colors::reset << std::endl;
        }
        return 1;
    }
}
