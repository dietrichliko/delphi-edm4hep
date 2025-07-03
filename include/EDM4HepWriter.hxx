#pragma once

#include "phdst/Analysis.hxx"

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
    
    int runAnalysis(const std::string& options = " ");

    // User methods that can be called from Fortran
    void user00();
    int user01();
    void user02();
    void user99();

    static EDM4HepWriter& instance();
}

// C wrapper functions for Fortran interface
extern "C" {
    void user00_();
    void user01_(int * need);
    void user02_();
    void user99_();
}
