// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: Main program for DELPHI to EDM4hep conversion

#include <iostream>
#include <vector>
#include <memory>
#include <argparse/argparse.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <EDM4hepWriter.hpp>

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
        argparse::ArgumentParser program("delphi_edm4hep", "1.0.0");
        
        // Customize program description with colors
        program.add_description(colors::bold + colors::cyan + 
                               "DELPHI to EDM4hep Conversion Program" + colors::reset + "\n" +
                               colors::green + 
                               "Convert DELPHI DST files to EDM4hep format for modern analysis frameworks" + 
                               colors::reset);
        
        // Add command line arguments
        program.add_argument("input_files")
            .help(colors::yellow + "Input DELPHI DST files to convert (optional, uses PDLINPUT if not specified)" + colors::reset)
            .nargs(argparse::nargs_pattern::any)
            .metavar("FILE");
        
        program.add_argument("-o", "--output")
            .help(colors::yellow + "Output EDM4hep file path" + colors::reset + " (required)")
            .required()
            .metavar("OUTPUT_FILE");
        
        program.add_argument("--max-events", "-n")
            .help(colors::yellow + "Maximum number of events to convert" + colors::reset + 
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
        std::string output_file = program.get<std::string>("--output");
        int max_events = program.get<int>("--max-events");
        
        // Log configuration
        spdlog::info("DELPHI to EDM4hep Conversion Starting");
        spdlog::info("Configuration:");
        
        if (input_files.empty()) {
            spdlog::info("  Input files: Using PDLINPUT file");
        } else {
            spdlog::info("  Input files: {} files", input_files.size());
            for (size_t i = 0; i < input_files.size(); ++i) {
                spdlog::info("    {}: {}", i + 1, input_files[i]);
            }
        }
        
        spdlog::info("  Output file: {}", output_file);
        spdlog::info("  Max events:  {}", max_events == 0 ? "unlimited" : std::to_string(max_events));
        spdlog::info("  Log level:   {}", log_level);
        
        // Create EDM4hep writer instance
        spdlog::info("Creating EDM4hep writer instance");
        auto writer = std::make_unique<EDM4hepWriter>();
        
        // Configure writer
        writer->setOutput(output_file);
        
        if (max_events > 0) {
            writer->setMaxEvent(max_events);
        }
        
        // Set input files if provided via command line
        if (!input_files.empty()) {
            for (const auto& file : input_files) {
                writer->setInput(file);
            }
        } else {
            spdlog::info("No input files specified - using PDLINPUT file for input configuration");
        }
        
        // Run conversion
        spdlog::info("Starting DELPHI to EDM4hep conversion");
        int status = writer->run();
        
        if (status == 0) {
            spdlog::info("Conversion completed successfully");
        } else {
            spdlog::error("Conversion completed with status: {}", status);
            return status;
        }
        
        // Writer object will be destroyed here, calling user99()
        spdlog::info("DELPHI to EDM4hep Conversion Completed");
        
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