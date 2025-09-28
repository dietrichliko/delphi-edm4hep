// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: PHDST common block PHCIII wrapper

/**
 * @file phciii.hpp
 * @brief PHDST common block PHCIII for event identification information
 * 
 * This header provides C++ access to the PHDST Fortran common block PHCIII,
 * which contains event identification and run information. The common block
 * is mapped to a C structure and accessible through convenient C++ references.
 * 
 * The PHCIII common block contains essential event metadata used throughout
 * the DELPHI analysis framework for event identification and bookkeeping.
 */

#pragma once

namespace phdst
{
    /**
     * @brief Fortran common block PHCIII structure
     * 
     * C structure mapping for the Fortran common block PHCIII.
     * This structure provides direct access to the event identification
     * variables used by the PHDST framework.
     * 
     * @note This structure maps directly to Fortran memory layout
     */
    extern "C" struct
    {
        int iiiexp; ///< Experiment number
        int iiirun; ///< Run number
        int iifile; ///< File number
        int iiievt; ///< Event number
        int iiidat; ///< Date 
        int iiitim; ///< Time 
        int iifill; ///< Fill number
    } phciii_;

    /**
     * @brief Reference to experiment number
     * 
     * Provides access to the experiment number.
     * Can be ignored for DELPHI data as it is always 1000.
     */
    inline int &IIIEXP = phciii_.iiiexp;
    
    /**
     * @brief Reference to run number
     * 
     * Provides access to the run number.
     */
    inline int &IIIRUN = phciii_.iiirun;
    
    /**
     * @brief Reference to file number
     * 
     * Provides access to the file number
     * This identifies the file within a run.
     * Its used for metadata matching
     */
    inline int &IIFILE = phciii_.iifile;
    
    /**
     * @brief Reference to event number
     * 
     * Provides access to the event number.
     * This is the unique event identifier within a file.
     */
    inline int &IIIEVT = phciii_.iiievt;
    
    /**
     * @brief Reference to date information
     * 
     * Provides access to the date information.
     */
    inline int &IIIDAT = phciii_.iiidat;
    
    /**
     * @brief Reference to time information
     * 
     * Provides access to the time information 
     */
    inline int &IIITIM = phciii_.iiitim;
    
    /**
     * @brief Reference to fill number
     * 
     * Provides access to the LEP fill number.
     */
    inline int &IIFILL = phciii_.iifill;

}