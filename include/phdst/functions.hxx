#pragma once

extern "C" void phdst_(char *, int *, int *, size_t);

namespace phdst {
    /**
     * @brief Calls the Fortran PHDST function with the given options.
     * 
     * @param options A string containing options for the PHDST function.
     * @return An integer flag indicating the status of the operation.
     */
    inline int PHDST(const std::string& options = " ") {
        int idummy = 0;        
        int iflag = 0
        // phdst_ does not change the content of options
        phdst_(const_cast<char*>(options.c_str()), idummy, iflag, options.size());
        return iflag;
    }

} // namespace phdst