// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#ifndef DELPHI_EDM4HEP_RunHeaderDATA_H
#define DELPHI_EDM4HEP_RunHeaderDATA_H

#include "delphi_edm4hep/Vector3f.h"
#include <cstdint>

namespace delphi {


/** @class RunHeaderData
 *  DELPHI-specific run header information
 *  @author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
 */
class RunHeaderData {
public:
  std::uint32_t experimentNumber{}; ///< Experiment number (always 1000 for DELPHI)
  std::uint32_t runNumber{}; ///< Run number
  std::uint32_t fileNumber{}; ///< File number within the run
  std::uint32_t fillNumber{}; ///< LEP fill number
  std::uint32_t startTime{}; ///< Run start time (Unix timestamp)
  std::uint32_t endTime{}; ///< Run end time (Unix timestamp)
  float beamEnergy{}; ///< LEP beam energy in GeV
  ::delphi::Vector3f beamSpot{}; ///< Beam spot position

};

} // namespace delphi


#endif
