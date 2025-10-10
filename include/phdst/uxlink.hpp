// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: PHDST common block UXLINK wrapper

/**
 * @file uxlink.hpp
 * @brief PHDST common block UXLINK for Zebra datastructure pointers
 * 
 * This header provides C++ access to the PHDST Fortran common block UXLINK,
 * which contains integer pointers to various sections of the main Zebra
 * datastructure. These L-variables serve as indices or addresses within
 * the Zebra memory management system used by DELPHI for dynamic data storage.
 * 
 * Zebra was the CERN data management system used for dynamic memory allocation
 * and data structure organization in Fortran-based physics analysis programs.
 * The L-variables in this common block point to different data sections
 * within the main Zebra store, enabling efficient access to reconstructed
 * physics objects and event information.
 */

#pragma once

namespace phdst
{
    /**
     * @brief Fortran common block UXLINK structure
     * 
     * C structure mapping for the Fortran common block UXLINK.
     * This structure provides direct access to integer pointers that
     * reference various sections of the main Zebra datastructure.
     * 
     * @note All L-variables are integer pointers to Zebra datastructure sections
     * @note This structure maps directly to Fortran memory layout
     */
    extern "C" struct
    {
        int ltemp[2];   ///< Integer pointer to temporary data section in Zebra store
        int lrtop;   ///< Integer pointer to reconstructed track top-level section
        int lstop;   ///< Integer pointer to shower/cluster top-level section
        int lttop;   ///< Integer pointer to trigger top-level section
        int litop;   ///< Integer pointer to identification top-level section
        int lrtemp;  ///< Integer pointer to reconstructed temporary data section
        int lrwtmp;  ///< Integer pointer to raw temporary data section
        int lrawux;  ///< Integer pointer to raw data section
        int lbktop;  ///< Integer pointer to background/noise top-level section
        int lortop;  ///< Integer pointer to original reconstruction top-level section
        int lrtint;  ///< Integer pointer to reconstruction intermediate section
        int ldtop;   ///< Integer pointer to detector top-level section
    } uxlink_;
    
    /**
     * @brief Reference to reconstructed track top-level section pointer
     * 
     * Integer pointer to the top-level section containing reconstructed
     * track information in the main Zebra datastructure. Provides access
     * to particle trajectory and momentum measurements.
     */
    inline int &LRTOP = uxlink_.lrtop;
    
    /**
     * @brief Reference to shower/cluster top-level section pointer
     * 
     * Integer pointer to the top-level section containing electromagnetic
     * shower and cluster information in the main Zebra datastructure.
     * Used for accessing calorimeter reconstruction data.
     */
    inline int &LSTOP = uxlink_.lstop;
    
    /**
     * @brief Reference to trigger top-level section pointer
     * 
     * Integer pointer to the top-level section containing trigger
     * information in the main Zebra datastructure. Provides access
     * to trigger decision and timing data.
     */
    inline int &LTTOP = uxlink_.lttop;
    
    /**
     * @brief Reference to identification top-level section pointer
     * 
     * Integer pointer to the top-level section containing particle
     * identification information in the main Zebra datastructure.
     * Used for accessing PID algorithms and results.
     */
    inline int &LITOP = uxlink_.litop;
    
    /**
     * @brief Reference to reconstructed temporary data section pointer
     * 
     * Integer pointer to temporary storage for reconstructed data
     * in the main Zebra datastructure. Used during intermediate
     * reconstruction processing steps.
     */
    inline int &LRTEMP = uxlink_.lrtemp;
    
    /**
     * @brief Reference to raw temporary data section pointer
     * 
     * Integer pointer to temporary storage for raw detector data
     * in the main Zebra datastructure. Used during raw data
     * processing before reconstruction.
     */
    inline int &LRWTMP = uxlink_.lrwtmp;
    
    /**
     * @brief Reference to raw data section pointer
     * 
     * Integer pointer to the raw detector data section in the main
     * Zebra datastructure. Provides access to unprocessed detector
     * readout information.
     */
    inline int &LRAWUX = uxlink_.lrawux;
    
    /**
     * @brief Reference to background/noise top-level section pointer
     * 
     * Integer pointer to the top-level section containing background
     * and noise information in the main Zebra datastructure. Used
     * for accessing detector noise characterization and subtraction.
     */
    inline int &LBKTOP = uxlink_.lbktop;
    
    /**
     * @brief Reference to original reconstruction top-level section pointer
     * 
     * Integer pointer to the top-level section containing original
     * reconstruction results in the main Zebra datastructure. May
     * be used for comparison with updated reconstruction algorithms.
     */
    inline int &LORTOP = uxlink_.lortop;
    
    /**
     * @brief Reference to reconstruction intermediate section pointer
     * 
     * Integer pointer to intermediate reconstruction data section
     * in the main Zebra datastructure. Contains partial reconstruction
     * results and intermediate calculations.
     */
    inline int &LRTINT = uxlink_.lrtint;
    
    /**
     * @brief Reference to detector top-level section pointer
     * 
     * Integer pointer to the top-level section containing detector
     * geometry and calibration information in the main Zebra
     * datastructure. Provides access to detector description data.
     */
    inline int &LDTOP = uxlink_.ldtop;

} // namespace phdst