// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: PHDST common block PXCHDR wrapper

/**
 * @file pxchdr.hpp
 * @brief PHDST common block PXCHDR for pilot record access
 * 
 * This header provides C++ access to the PHDST Fortran common block PXCHDR,
 * which contains the pilot record of events. The pilot record contains
 * essential event information that can be used for event selection without
 * reading the complete event structure, enabling efficient event filtering.
 * 
 * The pilot record is a compact representation of key event characteristics
 * that allows for fast event scanning and selection criteria application
 * before committing to reading the full event data.
 */

#pragma once

namespace phdst
{
    /**
     * @brief Fortran common block PXCHDR structure
     * 
     * C structure mapping for the Fortran common block PXCHDR.
     * This structure provides direct access to the pilot record data
     * used for efficient event selection and filtering.
     * 
     * @note This structure maps directly to Fortran memory layout
     */
    extern "C" struct
    {
        int nwpilt;      ///< Number of words in the pilot record
        int iupilt[1024]; ///< Pilot record data array (1024 words maximum)
    } pxchdr_;

    /**
     * @brief Reference to number of words in pilot record
     * 
     * Contains the actual number of words used in the IUPILT pilot record array.
     * This value indicates how much of the 1024-word array contains valid data.
     */
    inline int &NWPILT = pxchdr_.nwpilt;
    
    /**
     * @brief Alias for number of words in pilot record
     * 
     * Alternative name for NWPILT, providing the same functionality.
     * Contains the number of valid words in the pilot record.
     */
    inline int &NPILOT = pxchdr_.nwpilt;
    
    /**
     * @brief Access to pilot record data array (1-based indexing)
     * 
     * Provides access to the pilot record data array using Fortran-style
     * 1-based indexing. The pilot record contains essential event information
     * that can be used to select events without reading the whole event structure.
     * 
     * This enables efficient event filtering by examining key characteristics
     * (such as trigger information, basic kinematic variables, detector status)
     * before deciding whether to process the complete event data.
     * 
     * @param i Index into the pilot record array (1-based, range: 1 to NWPILT)
     * @return Reference to the i-th word of the pilot record
     * 
     * @note Uses 1-based indexing to match Fortran conventions
     * @note Array bounds are not checked - ensure i is in range [1, NWPILT]
     * @note The pilot record structure and content depend on the specific
     *       DELPHI data format and PHDST version being used
     * 
     * @warning Accessing beyond NWPILT may return undefined data
     */
    inline int &IUPILT(int i) { return pxchdr_.iupilt[i - 1]; }
    
    /**
     * @brief Alternative access to pilot record data array (1-based indexing)
     * 
     * Alias for IUPILT providing the same functionality with an alternative name.
     * Provides access to the pilot record data array using Fortran-style
     * 1-based indexing for event selection without reading complete structures.
     * 
     * @param i Index into the pilot record array (1-based, range: 1 to NPILOT)
     * @return Reference to the i-th word of the pilot record
     * 
     * @note Uses 1-based indexing to match Fortran conventions
     * @note Array bounds are not checked - ensure i is in range [1, NPILOT]
     * 
     * @see IUPILT for detailed documentation on pilot record usage
     */
    inline int &IPILOT(int i) { return pxchdr_.iupilt[i - 1]; }

} // namespace phdst