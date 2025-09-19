#pragma once

#include <string>
#include <vector>

class EDM4HepWriter {

private:

    // Private constructor for singleton
    EDM4HepWriter() = default;
    // Delete copy constructor and assignment operator
    EDM4HepWriter(const EDM4HepWriter&) = delete;
    EDM4HepWriter& operator=(const EDM4HepWriter&) = delete;
    // Delete move constructor and assignment operator
    EDM4HepWriter(EDM4HepWriter&&) = delete;
    EDM4HepWriter& operator=(EDM4HepWriter&&) = delete;

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

    std::vector<std::string> pdl_input_lines_;
    int max_events_ = -1; // Default to all events

    static EDM4HepWriter& instance();
};

