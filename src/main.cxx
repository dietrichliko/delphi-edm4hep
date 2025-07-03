#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "argparse/argparse.hpp"
#include "yaml-cpp/yaml.h"
#include "delphi-edm4hep_version.hpp"


int main(int argc, char *argv[])
{
  argparse::ArgumentParser program("delphi-edm4hep", DELPHI_EDM4HEP_VERSION);

  auto &group = program.add_mutually_exclusive_group(true);

  group.add_argument("-N", "--nickname")
      .metavar("NICKNAME")
      .help("Fatmen nickname of the sample");

  group.add_argument("-P", "--pdlinput")
      .metavar("FILE")
      .help("Path to the pdl input file");

  program.add_argument("-C", "--config")
      .metavar("FILE")
      .help("Path to the yaml configuration file")
      .required();
  
  program.add_argument("-O", "--output")
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

  // Define input file for PHDST
  if (int rc = create_pdlinput(program))
  {
    return rc;
  }

  // Load configuration file

  auto config = program.get<std::string>("--config");  
  std::cout << "config: " << config << std::endl;

  try
  {
    YAML::Node configNode = YAML::LoadFile(config);
  }
  catch (const YAML::BadFile &err)
  {
    std::cerr << "ERROR: Unable to open file " << config << std::endl;
    return 1;
  }

  auto EDM4HepWriter::instance();

  instance.runAnalysis();

}

int create_pdlinput(const argparse::ArgumentParser &program)
{
  std::filesystem::remove("PDLINPUT");

  if (auto nickname = program.present("--nickname"))
  {
    std::cout << "nickname: " << nickname.value() << std::endl;
    std::ofstream pdlinput("PDLINPUT");
    if (pdlinput.is_open())
    {
      pdlinput << "FAT = " << nickname.value() << std::endl;
      pdlinput.close();
    }
    else
    {
      std::cerr << "ERROR: Unable to open file PDLINPUT" << std::endl;
      return 1;
    }
  }
  else
  {
    auto pdlinput = std::filesystem::path(program.get("--pdlinput"));
    std::cout << "pdlinput: " << pdlinput << std::endl;
    if (!std::filesystem::exists(pdlinput))
    {
      std::cerr << "ERROR: File " << pdlinput << " does not exist" << std::endl;
      return 1;
    }
    std::filesystem::create_symlink(pdlinput, "PDLINPUT");
  }
  return 0;
}
  



