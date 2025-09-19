#include <iostream>
#include <fstream>
#include <string>
#include "argparse/argparse.hpp"
#include "yaml-cpp/yaml.h"
#include "spdlog/spdlog.h"
#include "delphi-edm4hep_version.hpp"

#include "skelana/functions.hpp"
#include "EDM4HepWriter.hpp"

namespace sk = skelana;

int main(int argc, char *argv[])
{
  spdlog::set_level(spdlog::level::info); // Set global log level to info
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v"); // Set log pattern

  argparse::ArgumentParser program("delphi-edm4hep", DELPHI_EDM4HEP_VERSION);

  program.add_description("A tool to convert DELPHI data to EDM4Hep format.");

  program.add_argument("-i", "--input")
      .metavar("FILE")
      .append()
      .help("Path to the Zebra input file");

  program.add_argument("-c", "--config")
      .metavar("FILE")
      .help("Path to the yaml configuration file")
      .required();
  
  program.add_argument("-o", "--output")
      .metavar("FILE")
      .help("Output file name")
      .required();

  program.add_argument("-m", "--max-events")
      .metavar("N")
      .help("Maximum number of events to process")
      .scan<'i', int>();

  try {
      program.parse_args(argc, argv);
  }
  catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  spdlog::info("Starting delphi-edm4hep version {}", DELPHI_EDM4HEP_VERSION);

  auto& writer = EDM4HepWriter::instance();

  // define input source

  for ( auto input : program.get<std::vector<std::string>>("--input") ) {
    writer.addPDLInput("FILE = " + input);
  }

  // Load configuration file

  auto config = program.get<std::string>("--config");  
  std::cout << "config: " << config << std::endl;

  try
  {
    YAML::Node configNode = YAML::LoadFile(config);
    if (configNode["skelana_flags"]) {
        auto flags = configNode["skelana_flags"];
        for (const auto& it : flags) {
            std::string option = it.first.as<std::string>();
            int value = it.second.as<int>();
            spdlog::info("Setting skelana option {} to {}", option, value);
            sk::SET_FLAG(option, value);
        }
    } else {
        spdlog::warn("No skelana_flags found in configuration file.");
    }
  }
  catch (const YAML::BadFile &err)
  {
    std::cerr << "ERROR: Unable to open file " << config << std::endl;
    return 1;
  }

  if (program.is_used("--max-events")) {
      int maxEvents = program.get<int>("--max-events");
      writer.setMaxEvents(maxEvents);
      spdlog::info("Set maximum events to process: {}", maxEvents);
  }



  writer.runAnalysis();

}
