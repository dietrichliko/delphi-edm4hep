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



MutableRunHeader::MutableRunHeader() :
  m_obj(new RunHeaderObj{}, podio::utils::MarkOwned) {}

MutableRunHeader::MutableRunHeader(std::uint32_t experimentNumber, std::uint32_t runNumber, std::uint32_t fileNumber, std::uint32_t fillNumber, std::uint32_t startTime, std::uint32_t endTime, float beamEnergy, delphi::Vector3f beamSpot) :
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

MutableRunHeader& MutableRunHeader::operator=(MutableRunHeader other) {
  swap(*this, other);
  return *this;
}

MutableRunHeader MutableRunHeader::clone() const {
  return MutableRunHeader(podio::utils::MaybeSharedPtr(new RunHeaderObj(*m_obj), podio::utils::MarkOwned));
}

MutableRunHeader::MutableRunHeader(podio::utils::MaybeSharedPtr<RunHeaderObj> obj) : m_obj(std::move(obj)) {}
MutableRunHeader::operator RunHeader() const { return RunHeader(m_obj); }

std::uint32_t MutableRunHeader::getExperimentNumber() const { return m_obj->data.experimentNumber; }
std::uint32_t MutableRunHeader::getRunNumber() const { return m_obj->data.runNumber; }
std::uint32_t MutableRunHeader::getFileNumber() const { return m_obj->data.fileNumber; }
std::uint32_t MutableRunHeader::getFillNumber() const { return m_obj->data.fillNumber; }
std::uint32_t MutableRunHeader::getStartTime() const { return m_obj->data.startTime; }
std::uint32_t MutableRunHeader::getEndTime() const { return m_obj->data.endTime; }
float MutableRunHeader::getBeamEnergy() const { return m_obj->data.beamEnergy; }
const delphi::Vector3f& MutableRunHeader::getBeamSpot() const { return m_obj->data.beamSpot; }


void MutableRunHeader::setExperimentNumber(std::uint32_t value) { m_obj->data.experimentNumber = value; }
void MutableRunHeader::setRunNumber(std::uint32_t value) { m_obj->data.runNumber = value; }
void MutableRunHeader::setFileNumber(std::uint32_t value) { m_obj->data.fileNumber = value; }
void MutableRunHeader::setFillNumber(std::uint32_t value) { m_obj->data.fillNumber = value; }
void MutableRunHeader::setStartTime(std::uint32_t value) { m_obj->data.startTime = value; }
void MutableRunHeader::setEndTime(std::uint32_t value) { m_obj->data.endTime = value; }
void MutableRunHeader::setBeamEnergy(float value) { m_obj->data.beamEnergy = value; }
void MutableRunHeader::setBeamSpot(delphi::Vector3f value) { m_obj->data.beamSpot = value; }
delphi::Vector3f& MutableRunHeader::beamSpot() { return m_obj->data.beamSpot; }







bool MutableRunHeader::isAvailable() const {
  if (m_obj) {
    return true;
  }
  return false;
}

const podio::ObjectID MutableRunHeader::getObjectID() const {
  if (m_obj) {
    return m_obj->id;
  }
  return podio::ObjectID{};
}

bool MutableRunHeader::operator==(const RunHeader& other) const {
  return m_obj == other.m_obj;
}

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
void to_json(nlohmann::json& j, const MutableRunHeader& value) {
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

