#pragma once

#include <string>
#include <vector>
#include <memory>
#include <podio/Frame.h>
#include <podio/ROOTWriter.h>   

class EDM4HepWriter {

private:
    std::string output_file_ = "output.edm4hep.root";    
    std::vector<std::string> pdl_input_lines_;
    int max_events_ = -1; // Default to all events
    int file_number_;
    int last_run_number_ = -1;
    int last_file_number_ = -1;
    std::unique_ptr<podio::ROOTWriter> writer_;

    // Private constructor for singleton
    EDM4HepWriter() = default;
    // Delete copy constructor and assignment operator
    EDM4HepWriter(const EDM4HepWriter&) = delete;
    EDM4HepWriter& operator=(const EDM4HepWriter&) = delete;
    // Delete move constructor and assignment operator
    EDM4HepWriter(EDM4HepWriter&&) = delete;
    EDM4HepWriter& operator=(EDM4HepWriter&&) = delete;

    podio::Frame createRunFrame();
    podio::Frame createEventFrame();

    bool is_mc() const();

public:
    // Destructor
    ~EDM4HepWriter() = default; 
    
    void addPDLInput(const std::string& line);
    void setOutput(const std::string& output);
    void setMaxEvents(int maxEvents);
    void setSkelanaFlag(const std::string& options, const int value);

    int runAnalysis(const std::string& options = " ");

    // User methods that can be called from Fortran
    void user00();
    int user01();
    void user02();
    void user99();
    static EDM4HepWriter& instance();

};

