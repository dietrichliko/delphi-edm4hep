#include "phdst.hxx"
#include "EDM4HepWriter.hxx"

void EDM4HepWriter::user00() {
    std::cout << "EDM4HepWriter::user00() called" << std::endl;

}

int EDM4HepWriter::user01() {
    std::cout << "EDM4HepWriter::user01() called" << std::endl;
    // Call the Fortran function and return an integer flag
    return 0; // Replace with actual logic if needed
}

void EDM4HepWriter::user02() {
    std::cout << "EDM4HepWriter::user02() called" << std::endl;
    // Call the Fortran function for user02
}

void EDM4HepWriter::user99() {
    std::cout << "EDM4HepWriter::user99() called" << std::endl;
    // Call the Fortran function for user99
}


int EDM4HepWriter::runAnalysis(const std::string& options) {
    // Call the Fortran function with the provided options
    return PHDST(options);
}

void user00() {
    EDM4HepWriter::instance().user00();
}

int user01() {
    return EDM4HepWriter::instance().user01();
}

void user02() {
    EDM4HepWriter::instance().user02();
}

void user99() {
    EDM4HepWriter::instance().user99();
}