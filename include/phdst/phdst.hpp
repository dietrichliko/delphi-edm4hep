// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: Wrapper for PHDST Fortran library


/**
 * @file phdst.hpp
 * @brief Main header for PHDST (Physics Data Summary Tape) functionality
 * 
 * This header provides C++ wrappers for the legacy DELPHI PHDST Fortran library,
 * enabling modern C++ code to interact with DELPHI DST (Data Summary Tape) files.
 * 
 * PHDST is the core library used by the DELPHI experiment at CERN's LEP collider
 * for reading and processing physics data stored in DST format. This wrapper
 * maintains compatibility with the original Fortran interface while providing
 * type-safe, convenient C++ functions.
 * 
 * Key features:
 * - Type-safe wrappers converting between C++ std::string and Fortran strings
 * - Memory-safe handling of Fortran calling conventions
 * - Seamless integration with modern C++ codebases
 * - Preservation of original PHDST functionality and semantics
 * 
 * Usage:
 * @code
 * #include <phdst/phdst.hpp>
 * 
 * // Initialize PHDST system
 * int status = phdst::PHDST("");
 * if (status != 0) {
 *     // Handle initialization error
 * }
 * @endcode
 * 
 * @note This wrapper is designed for the DELPHI-EDM4hep conversion project,
 *       which translates legacy DELPHI data into the modern EDM4hep format.
 * 
 * @see functions.hpp for individual function wrappers
 * @see https://cds.cern.ch/record/002629128 PHDST User Manual
 */

#pragma once
#include <phdst/functions.hpp>
#include <phdst/phciii.hpp>
#include <phdst/phgen.hpp>
#include <phdst/phlun.hpp>
#include <phdst/pxchdr.hpp>
#include <phdst/uxcom.hpp>
#include <phdst/uxlink.hpp>
#include <phdst/zebra_pointer.hpp>
