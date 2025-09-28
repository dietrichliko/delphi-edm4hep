// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: PHDST common block UXCOM wrapper for Zebra memory management

/**
 * @file uxcom.hpp
 * @brief PHDST common block UXCOM for Zebra memory management system
 * 
 * This header provides C++ access to the PHDST Fortran common block UXCOM,
 * which contains the main Zebra memory management arrays and structures.
 * Zebra was CERN's dynamic memory management system used in Fortran-based
 * physics analysis programs.
 * 
 * The Zebra system organizes data in "banks" - structured memory blocks
 * that can contain physics data. Each bank is accessed through integer
 * pointers, and data within banks can be accessed as integers (IQ) or
 * floating-point values (Q). Links between banks are stored in LQ arrays.
 * 
 * @par Zebra Bank Structure:
 * A Zebra bank starting at position I contains:
 * - Real values: Q(I+offset) for floating-point data
 * - Integer values: IQ(I+offset) for integer data  
 * - Links: LQ(I-1) and similar for pointers to related banks
 * 
 * @par Memory Layout:
 * @code
 * COMMON /UXCOM/ UXFENC(10), LUXSTR(NLNKMX), LUXREF(NLNKMX)
 * REAL Q(NSIZEQ)
 * INTEGER IQ(NSIZEQ), LQ(NSIZEQ)
 * EQUIVALENCE (LQ(1), LUXSTR(1)), (Q(1), IQ(1), LQ(9))
 * @endcode
 */

#pragma once
#include <cstddef>

namespace phdst
{
    /**
     * @brief Maximum number of links in Zebra system
     * 
     * Corresponds to NLNKMX parameter in the Fortran code.
     * Defines the maximum number of link structures.
     */
    constexpr int NLNKMX = 30;
    
    /**
     * @brief Fortran common block UXCOM structure
     * 
     * C structure mapping for the Fortran common block UXCOM.
     * To avoid alignment issues, we map the entire common block as integers
     * and provide access functions that handle the proper interpretation.
     * 
     * Memory layout matches:
     * COMMON /UXCOM/ UXFENC(10), LUXSTR(NLNKMX), LUXREF(NLNKMX)
     * EQUIVALENCE (LQ(1), LUXSTR(1)), (Q(1), IQ(1), LQ(9))
     * 
     * @note Mapped as integer array to avoid float/int alignment issues
     */
    extern "C" struct
    {
        int data[10 + NLNKMX + NLNKMX];  ///< Entire common block as integer array
    } uxcom_;
    

    
    /**
     * @brief Access integer data in Zebra memory
     * 
     * Provides access to Zebra memory as integer values. This corresponds
     * to the IQ array in the Fortran code. Based on equivalence:
     * (Q(1), IQ(1), LQ(9)) means IQ(1) = LUXSTR(9)
     * 
     * @param i Index into the Zebra memory (1-based Fortran indexing)
     * @return Reference to integer value at position i
     * 
     * @note Uses 1-based indexing to match Fortran conventions
     * @note IQ(1) corresponds to LUXSTR(9) due to equivalence
     */
    inline int &IQ(int i) { 
        return uxcom_.data[10 + i + 7]; // 10 (UXFENC) + i + 8-1 (LQ(9) offset)
    }
    
    /**
     * @brief Access floating-point data in Zebra memory
     * 
     * Provides access to Zebra memory as floating-point values. This corresponds
     * to the Q array in the Fortran code. Q shares the same memory as IQ.
     * 
     * @param i Index into the Zebra memory (1-based Fortran indexing)
     * @return Reference to float value at position i
     * 
     * @note Uses 1-based indexing to match Fortran conventions
     * @note Q(1) = IQ(1) due to equivalence
     * @note Reinterprets integer memory as float - assumes IEEE754 compatibility
     */
    inline float &Q(int i) { 
        return *reinterpret_cast<float*>(&uxcom_.data[10 + i + 7]);
    }
    
    /**
     * @brief Access link pointers in Zebra memory
     * 
     * Provides access to Zebra memory as link pointers. This corresponds
     * to the LQ array in the Fortran code. Based on equivalence:
     * LQ(1) = LUXSTR(1)
     * 
     * @param i Index into the Zebra memory (1-based Fortran indexing)
     * @return Reference to link pointer at position i
     * 
     * @note Uses 1-based indexing to match Fortran conventions
     * @note LQ(1) corresponds to LUXSTR(1) due to equivalence
     */
    inline int &LQ(int i) { 
        return uxcom_.data[10 + i - 1]; // 10 (UXFENC) + i-1 (1-based to 0-based)
    }

} // namespace phdst