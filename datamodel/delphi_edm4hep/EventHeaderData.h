// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#ifndef DELPHI_EDM4HEP_EventHeaderDATA_H
#define DELPHI_EDM4HEP_EventHeaderDATA_H

#include "delphi_edm4hep/TimeStamp.h"
#include <cstdint>

namespace delphi {


/** @class EventHeaderData
 *  DELPHI-specific event header with extended metadata
 *  @author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
 */
class EventHeaderData {
public:
  std::uint32_t eventNumber{}; ///< Event number within the run
  std::uint32_t runNumber{}; ///< Run number
  std::uint32_t fileNumber{}; ///< File number within the run
  ::delphi::TimeStamp timeStamp{}; ///< Event timestamp
  std::uint32_t delphiDate{}; ///< Original DELPHI date format (YYMMDD)
  std::uint32_t delphiTime{}; ///< Original DELPHI time format (HHMMSS)

};

} // namespace delphi


#endif
