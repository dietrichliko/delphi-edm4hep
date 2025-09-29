// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#ifndef DELPHI_EDM4HEP_TimeStamp_H
#define DELPHI_EDM4HEP_TimeStamp_H

#include <cstdint>
#include <ostream>

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
#include "nlohmann/json_fwd.hpp"
#endif

namespace delphi {

/** @class TimeStamp
 *  
 *  @author: 
 */
class TimeStamp {
public:
  std::uint64_t unixTime{}; ///< Unix timestamp in seconds since epoch


};

std::ostream& operator<<(std::ostream& o, const delphi::TimeStamp& value);

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
void to_json(nlohmann::json& j, const TimeStamp& value);
#endif

} // namespace delphi


#endif
