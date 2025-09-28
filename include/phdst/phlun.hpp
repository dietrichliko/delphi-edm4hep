// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: PHDST common block PHLUN wrapper

/**
 * @file phlun.hpp
 * @brief PHDST common block PHLUN for Fortran I/O logical unit numbers
 * 
 * This header provides C++ access to the PHDST Fortran common block PHLUN,
 * which contains logical unit numbers (LUNs) used for Fortran I/O operations.
 * All LUNs are Fortran I/O identifiers that reference various files and
 * devices used by the PHDST framework.
 * 
 * In Fortran, logical unit numbers are integer identifiers that associate
 * file operations with specific files or devices. The PHLUN common block
 * centralizes these identifiers for consistent use throughout the PHDST system.
 */

#pragma once

namespace phdst
{
    /**
     * @brief Fortran common block PHLUN structure
     * 
     * C structure mapping for the Fortran common block PHLUN.
     * This structure provides direct access to all logical unit numbers
     * used by the PHDST framework for file I/O operations.
     * 
     * @note All members are Fortran I/O logical unit numbers (LUNs)
     * @note This structure maps directly to Fortran memory layout
     */
    extern "C" struct
    {
        int lundst; ///< Logical unit for DST (Data Summary Tape) files
        int lunstr; ///< Logical unit for stream files
        int lunlog; ///< Logical unit for log files
        int luntty; ///< Logical unit for terminal/TTY output
        int lunhst; ///< Logical unit for histogram files
        int lunhbo; ///< Logical unit for histogram booking files
        int lunpdl; ///< Logical unit for PDL (Process Description Language) files
        int lundsc; ///< Logical unit for descriptor files
        int lunptr[10]; ///< Array of logical units for pointer files
        int lunfat; ///< Logical unit for FAT (File Allocation Table) files
        int lunfan; ///< Logical unit for FAN files
        int lunzip; ///< Logical unit for compressed/ZIP files
    } phlun_;

    /**
     * @brief Reference to DST file logical unit number
     * 
     * Fortran I/O identifier for Data Summary Tape (DST) files.
     * Used for reading and writing the main physics data files.
     */
    inline int &LUNDST = phlun_.lundst;
    
    /**
     * @brief Reference to stream file logical unit number
     * 
     * Fortran I/O identifier for stream files used in data processing.
     */
    inline int &LUNSTR = phlun_.lunstr;
    
    /**
     * @brief Reference to log file logical unit number
     * 
     * Fortran I/O identifier for log files containing processing information
     * and diagnostic messages.
     */
    inline int &LUNLOG = phlun_.lunlog;
    
    /**
     * @brief Reference to terminal/TTY logical unit number
     * 
     * Fortran I/O identifier for terminal output, typically used for
     * interactive communication with the user.
     */
    inline int &LUNTTY = phlun_.luntty;
    
    /**
     * @brief Reference to histogram file logical unit number
     * 
     * Fortran I/O identifier for histogram files used to store
     * analysis results and plots.
     */
    inline int &LUNHST = phlun_.lunhst;
    
    /**
     * @brief Reference to histogram booking file logical unit number
     * 
     * Fortran I/O identifier for histogram booking files that contain
     * histogram definitions and booking information.
     */
    inline int &LUNHBO = phlun_.lunhbo;
    
    /**
     * @brief Reference to PDL file logical unit number
     * 
     * Fortran I/O identifier for Process Description Language (PDL) files
     * that contain analysis process definitions.
     */
    inline int &LUNPDL = phlun_.lunpdl;
    
    /**
     * @brief Reference to descriptor file logical unit number
     * 
     * Fortran I/O identifier for descriptor files containing metadata
     * and file structure information.
     */
    inline int &LUNDSC = phlun_.lundsc;
    
    /**
     * @brief Access to pointer file logical unit numbers array
     * 
     * Returns a reference to the i-th logical unit number for pointer files.
     * Pointer files contain index or reference information for data access.
     * 
     * @param i Index into the LUNPTR array (0-9)
     * @return Reference to the i-th pointer file logical unit number
     * @note Array bounds are not checked - ensure i is in range [0,9]
     */
    inline int &LUNPTR(int i) { return phlun_.lunptr[i]; }
    
    /**
     * @brief Reference to FAT file logical unit number
     * 
     * Fortran I/O identifier for File Allocation Table (FAT) files
     * used for file system management.
     */
    inline int &LUNFAT = phlun_.lunfat;
    
    /**
     * @brief Reference to FAN file logical unit number
     * 
     * Fortran I/O identifier for FAN files (specific to PHDST framework).
     */
    inline int &LUNFAN = phlun_.lunfan;
    
    /**
     * @brief Reference to ZIP file logical unit number
     * 
     * Fortran I/O identifier for compressed or ZIP files used for
     * data storage and transfer.
     */
    inline int &LUNZIP = phlun_.lunzip;

} // namespace phdst   