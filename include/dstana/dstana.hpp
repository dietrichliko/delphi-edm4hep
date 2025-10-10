#pragma once
// Copyright (c) 2025 Members of the DELPHI collaboration
// SPDX-License-Identifier: GPL-3.0-or-later
// Project: DELPHI-EDM4hep
//
// Author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
// Description: Wrapper for PHDST Fortran library

#include <string>

extern "C" void dstqid_(char* dstqID, int dstqID_len);
extern "C" void bpilot_(float* btesla, float* bgevcm);

namespace dstana {
/**
 * @brief Get the dataset version identifier (DSTQID)
 *
 * This function retrieves the dataset version identifier from
 * the DELPHI DST data. The identifier is typically a 4-character
 * string like "94B2", indicating the year, version, and DST type.
 *
 * @return Dataset version identifier as a std::string
 */
inline std::string DSTQID() {
  char dstqID[5] = "    "; // 4 chars + null terminator
  dstqid_(dstqID, 4);
  return std::string(dstqID);
}

/**
 * @brief Get beam and magnetic field information
 *
 * This function retrieves the magnetic field strength and beam energy
 * information from the DELPHI pilot data structures.
 * Also various common blocks are filled, so the magnetic field is available
 * in various FORTRAN routines.
 *
 * @param btesla Reference to float where magnetic field strength (in Tesla) will be stored
 * @param bgevcm Reference to float where beam energy per beam (in GeV) will be stored
 */
inline void BPILOT(float& btesla, float& bgevcm) {
  bpilot_(&btesla, &bgevcm);
}


} // namespace dstana
