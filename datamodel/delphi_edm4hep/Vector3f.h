// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#ifndef DELPHI_EDM4HEP_Vector3f_H
#define DELPHI_EDM4HEP_Vector3f_H

#include <ostream>

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
#include "nlohmann/json_fwd.hpp"
#endif

namespace delphi {

/** @class Vector3f
 *  
 *  @author: 
 */
class Vector3f {
public:
  float x{};
  float y{};
  float z{};

constexpr Vector3f() : x(0),y(0),z(0) {}
constexpr Vector3f(float xx, float yy, float zz) : x(xx),y(yy),z(zz) {}
constexpr Vector3f(const float* v) : x(v[0]),y(v[1]),z(v[2]) {}
constexpr bool operator==(const Vector3f& v) const { return (x==v.x&&y==v.y&&z==v.z) ; }
constexpr float operator[](unsigned i) const { return *( &x + i ) ; }


};

std::ostream& operator<<(std::ostream& o, const delphi::Vector3f& value);

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
void to_json(nlohmann::json& j, const Vector3f& value);
#endif

} // namespace delphi


#endif
