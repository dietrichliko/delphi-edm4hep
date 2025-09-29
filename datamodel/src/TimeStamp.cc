// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#include "delphi_edm4hep/TimeStamp.h"

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
#include "nlohmann/json.hpp"
#endif

namespace delphi {


std::ostream& operator<<(std::ostream& o, const delphi::TimeStamp& value) {
  o << value.unixTime << " ";

  return o;
}

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
void to_json(nlohmann::json& j, const TimeStamp& value) {
  j = nlohmann::json{
  {"unixTime", value.unixTime}
  };
}
#endif

} // namespace delphi


