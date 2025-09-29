// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

// datamodel specific includes
#include "delphi_edm4hep/RunHeader.h"
#include "delphi_edm4hep/MutableRunHeader.h"
#include "delphi_edm4hep/RunHeaderObj.h"
#include "delphi_edm4hep/RunHeaderData.h"
#include "delphi_edm4hep/RunHeaderCollection.h"


#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
#include "nlohmann/json.hpp"
#endif

#include <ostream>

namespace delphi {



RunHeader::RunHeader() :
  m_obj(new RunHeaderObj{}, podio::utils::MarkOwned) {}

RunHeader::RunHeader(std::uint32_t experimentNumber, std::uint32_t runNumber, std::uint32_t fileNumber, std::uint32_t fillNumber, std::uint32_t startTime, std::uint32_t endTime, float beamEnergy, delphi::Vector3f beamSpot) :
  m_obj(new RunHeaderObj{}, podio::utils::MarkOwned) {
  m_obj->data.experimentNumber = experimentNumber;
  m_obj->data.runNumber = runNumber;
  m_obj->data.fileNumber = fileNumber;
  m_obj->data.fillNumber = fillNumber;
  m_obj->data.startTime = startTime;
  m_obj->data.endTime = endTime;
  m_obj->data.beamEnergy = beamEnergy;
  m_obj->data.beamSpot = beamSpot;
}

RunHeader& RunHeader::operator=(RunHeader other) {
  swap(*this, other);
  return *this;
}

MutableRunHeader RunHeader::clone() const {
  return MutableRunHeader(podio::utils::MaybeSharedPtr(new RunHeaderObj(*m_obj), podio::utils::MarkOwned));
}

RunHeader::RunHeader(podio::utils::MaybeSharedPtr<RunHeaderObj> obj) : m_obj(std::move(obj)) {}

RunHeader::RunHeader(RunHeaderObj* obj) : m_obj(podio::utils::MaybeSharedPtr<RunHeaderObj>(obj)) {}

RunHeader RunHeader::makeEmpty() {
  return {nullptr};
}

std::uint32_t RunHeader::getExperimentNumber() const { return m_obj->data.experimentNumber; }
std::uint32_t RunHeader::getRunNumber() const { return m_obj->data.runNumber; }
std::uint32_t RunHeader::getFileNumber() const { return m_obj->data.fileNumber; }
std::uint32_t RunHeader::getFillNumber() const { return m_obj->data.fillNumber; }
std::uint32_t RunHeader::getStartTime() const { return m_obj->data.startTime; }
std::uint32_t RunHeader::getEndTime() const { return m_obj->data.endTime; }
float RunHeader::getBeamEnergy() const { return m_obj->data.beamEnergy; }
const delphi::Vector3f& RunHeader::getBeamSpot() const { return m_obj->data.beamSpot; }






bool RunHeader::isAvailable() const {
  if (m_obj) {
    return true;
  }
  return false;
}

const podio::ObjectID RunHeader::getObjectID() const {
  if (m_obj) {
    return m_obj->id;
  }
  return podio::ObjectID{};
}

bool RunHeader::operator==(const MutableRunHeader& other) const {
  return m_obj == other.m_obj;
}

std::ostream& operator<<(std::ostream& o, const RunHeader& value) {
  if (!value.isAvailable()) {
    return o << "[not available]";
  }
  o << " id: " << value.id() << '\n';
  o << " experimentNumber : " << value.getExperimentNumber() << '\n';
  o << " runNumber : " << value.getRunNumber() << '\n';
  o << " fileNumber : " << value.getFileNumber() << '\n';
  o << " fillNumber : " << value.getFillNumber() << '\n';
  o << " startTime : " << value.getStartTime() << '\n';
  o << " endTime : " << value.getEndTime() << '\n';
  o << " beamEnergy : " << value.getBeamEnergy() << '\n';
  o << " beamSpot : " << value.getBeamSpot() << '\n';



  return o;
}

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
void to_json(nlohmann::json& j, const RunHeader& value) {
  j = nlohmann::json{
    {"experimentNumber", value.getExperimentNumber()}
    ,{"runNumber", value.getRunNumber()}
    ,{"fileNumber", value.getFileNumber()}
    ,{"fillNumber", value.getFillNumber()}
    ,{"startTime", value.getStartTime()}
    ,{"endTime", value.getEndTime()}
    ,{"beamEnergy", value.getBeamEnergy()}
    ,{"beamSpot", value.getBeamSpot()}
  };


}
#endif


} // namespace delphi

