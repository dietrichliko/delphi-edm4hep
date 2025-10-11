// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: Main program for DELPHI to EDM4hep conversion

#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <argparse/argparse.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <toml++/toml.h>
#include <edm4hep_writer.hpp>
#include <DELPHI_EDM4hepVersion.hpp>

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

/**
 * @brief Configuration structure to hold parsed command line arguments and config file
 */
struct Config {
    // File paths
    std::vector<std::string> input_files;
    std::string output_file;
    std::string config_file;
    
    // Logging configuration
    struct {
        std::string level = "info";
    } logging;
    
    // PHDST configuration
    struct {
        int max_events = 0;
        bool filter_t4_hadrons = false;
    } phdst;
    
    // EDM4hep configuration
    struct {
        bool fix_secondary_hadronic_interactions = true;
    } edm4hep;
};

/**
 * @brief Load configuration from TOML config file
 */
void loadConfigFile(Config& config, const std::string& config_file) {
    try {
        auto toml_config = toml::parse_file(config_file);
        
        // Load logging section
        if (auto logging = toml_config["logging"]) {
            if (auto level = logging["level"].value<std::string>()) {
                config.logging.level = *level;
            }
        }
        
        // Load phdst section
        if (auto phdst = toml_config["phdst"]) {
            if (auto max_events = phdst["max_events"].value<int>()) {
                config.phdst.max_events = *max_events;
            }
            if (auto filter_t4_hadrons = phdst["filter_t4_hadrons"].value<bool>()) {
                config.phdst.filter_t4_hadrons = *filter_t4_hadrons;
            }
        }
        
        // Load edm4hep section
        if (auto edm4hep = toml_config["edm4hep"]) {
            if (auto fix_secondary_hadronic_interactions = edm4hep["fix_secondary_hadronic_interactions"].value<bool>()) {
                config.edm4hep.fix_secondary_hadronic_interactions = *fix_secondary_hadronic_interactions;
            }
        }
        
        // Load input files if specified in config
        if (auto input_files = toml_config["input_files"]) {
            if (input_files.is_array()) {
                config.input_files.clear(); // Clear any existing files
                auto array = input_files.as_array();
                for (auto& file : *array) {
                    if (auto file_str = file.value<std::string>()) {
                        config.input_files.push_back(*file_str);
                    }
                }
            }
        }
        
        // Load output file if specified in config
        if (auto output_file = toml_config["output_file"].value<std::string>()) {
            config.output_file = *output_file;
        }
        
        spdlog::info("Configuration loaded from: {}", config_file);
        
    } catch (const toml::parse_error& e) {
        throw std::runtime_error("Failed to parse TOML config file '" + config_file + "': " + 
                               std::string(e.description()));
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to load config file '" + config_file + "': " + e.what());
    }
}

/**
 * @brief Parse command line arguments and return configuration
 */
Config parseArguments(int argc, char* argv[]) {
    // Configure argparse with colors and git version
    argparse::ArgumentParser program("delphi_edm4hep_writer", delphi::version::GIT_VERSION);
    
    // Customize program description with colors
    program.add_description(colors::bold + colors::cyan + 
                           "DELPHI to EDM4hep Conversion Program" + colors::reset + "\n" +
                           colors::green + 
                           "Convert DELPHI DST files to EDM4hep format for modern analysis frameworks" + 
                           colors::reset + "\n\n" +
                           colors::magenta + "Version Information:" + colors::reset + "\n" +
                           "  Git Version: " + colors::yellow + delphi::version::GIT_VERSION + colors::reset + "\n" +
                           "  Project:     " + colors::yellow + delphi::version::PROJECT_VERSION + colors::reset + "\n" +
                           "  Build Type:  " + colors::yellow + delphi::version::BUILD_TYPE + colors::reset + "\n" +
                           "  Compiler:    " + colors::yellow + delphi::version::COMPILER + colors::reset);
    
    // Add command line arguments
    program.add_argument("input_files")
        .help(colors::yellow + "Input DELPHI DST files to convert (optional, uses PDLINPUT if not specified)" + colors::reset)
        .nargs(argparse::nargs_pattern::any)
        .metavar("FILE");
    
    program.add_argument("-o", "--output")
        .help(colors::yellow + "Output EDM4hep file path" + colors::reset + " (can be overridden by config file)")
        .metavar("OUTPUT_FILE");
    
    program.add_argument("-c", "--config")
        .help(colors::yellow + "TOML configuration file path" + colors::reset)
        .metavar("CONFIG_FILE");
    
    program.add_argument("--max-events", "-n")
        .help(colors::yellow + "Maximum number of events to convert" + colors::reset + 
              " (0 = unlimited, overrides config file)")
        .default_value(-1)  // Use -1 to indicate not set
        .scan<'i', int>()
        .metavar("N");
    
    program.add_argument("--filter-t4-hadrons")
        .help(colors::yellow + "Filter T4 hadrons in event selection" + colors::reset + 
              " (overrides config file)")
        .flag();
    
    program.add_argument("--log-level", "-l")
        .help(colors::yellow + "Set log level" + colors::reset + 
              " (trace, debug, info, warn, error, critical, overrides config file)")
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
        throw; // Re-throw to be handled by main
    }
    
    // Create configuration with defaults
    Config config;
    
    // Load config file first if specified
    if (program.is_used("--config")) {
        config.config_file = program.get<std::string>("--config");
        loadConfigFile(config, config.config_file);
    }
    
    // Command line arguments override config file values
    
    // Input files from command line
    auto cmd_input_files = program.get<std::vector<std::string>>("input_files");
    if (!cmd_input_files.empty()) {
        config.input_files = cmd_input_files;
    }
    
    // Output file from command line
    if (program.is_used("--output")) {
        config.output_file = program.get<std::string>("--output");
    }
    
    // Validate that output file is specified (either from config or command line)
    if (config.output_file.empty()) {
        throw std::runtime_error("Output file must be specified either via --output or in config file");
    }
    
    // Max events from command line
    int cmd_max_events = program.get<int>("--max-events");
    if (cmd_max_events >= 0) {  // -1 means not set
        config.phdst.max_events = cmd_max_events;
    }
    
    // Filter T4 hadrons from command line
    if (program.get<bool>("--filter-t4-hadrons")) {
        config.phdst.filter_t4_hadrons = true;
    }
    
    // Log level from command line
    if (program.is_used("--log-level")) {
        config.logging.level = program.get<std::string>("--log-level");
    }
    
    // Verbose flag overrides log level
    if (program.get<bool>("--verbose")) {
        config.logging.level = "debug";
    }
    
    return config;
}

int main(int argc, char* argv[]) {
    try {
        // Parse command line arguments
        Config config = parseArguments(argc, argv);
        
        // Initialize logging
        setupLogging(config.logging.level);
        
        // Log configuration
        spdlog::info("DELPHI to EDM4hep Conversion Starting");
        spdlog::info("Version: {} ({})", delphi::version::GIT_VERSION, delphi::version::GIT_COMMIT_DATE);
        spdlog::info("Configuration:");
        
        if (!config.config_file.empty()) {
            spdlog::info("  Config file: {}", config.config_file);
        }
        
        if (config.input_files.empty()) {
            spdlog::info("  Input files: Using PDLINPUT file");
        } else {
            spdlog::info("  Input files: {} files", config.input_files.size());
            for (size_t i = 0; i < config.input_files.size(); ++i) {
                spdlog::info("    {}: {}", i + 1, config.input_files[i]);
            }
        }
        
        spdlog::info("  Output file: {}", config.output_file);
        spdlog::info("  Max events:  {}", config.phdst.max_events == 0 ? "unlimited" : std::to_string(config.phdst.max_events));
        spdlog::info("  Filter T4 hadrons: {}", config.phdst.filter_t4_hadrons ? "enabled" : "disabled");
        spdlog::info("  Fix secondary hadronic interactions: {}", config.edm4hep.fix_secondary_hadronic_interactions ? "enabled" : "disabled");
        spdlog::info("  Log level:   {}", config.logging.level);
        
        // Create EDM4hep writer instance
        spdlog::info("Creating EDM4hep writer instance");
        auto writer = std::make_unique<EDM4hepWriter>();
        
        // Configure writer
        writer->setOutput(config.output_file);
        writer->setFixSecondaryHadronicInteractions(config.edm4hep.fix_secondary_hadronic_interactions);
        
        if (config.phdst.max_events > 0) {
            writer->setMaxEvent(config.phdst.max_events);
        }

        if (config.phdst.filter_t4_hadrons) {
            writer->setFilterT4Hadrons(config.phdst.filter_t4_hadrons);
        }
        
        // Set input files if provided via command line
        if (!config.input_files.empty()) {
            for (const auto& file : config.input_files) {
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
        
        // Writer object will be destroyed here
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