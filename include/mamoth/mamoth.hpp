#pragma once
// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: Wrapper for MAMOTH Fortran library

#include <cstdint>

extern "C" {
    void makemod8_(std::uint32_t* lpa, int* flag, int* ierr);
}

namespace mamoth {
    /**
     * @brief Wrapper for MAKEMOD8 Fortran subroutine
     * 
     * This function calls the Fortran MAKEMOD8 subroutine which modifies
     * secondary hadronic interaction blocklets in the ZEBRA data structure.
     * 
     * @param lpa Reference to pointer to the particle association block (may be modified)
     * @param flag Boolean flag for the operation (converted to FORTRAN LOGICAL)
     * @return Error code from the FORTRAN routine
     */
    inline int MAKEMOD8(std::uint32_t& lpa, bool flag) {
        int ierr = 0;
        int fortran_logical = flag ? 1 : 0;  // Convert C++ bool to FORTRAN LOGICAL
        makemod8_(&lpa, &fortran_logical, &ierr);
        return ierr;
    }
}