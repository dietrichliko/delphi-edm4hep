// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

// datamodel specific includes
#include "delphi_edm4hep/EventHeader.h"
#include "delphi_edm4hep/MutableEventHeader.h"
#include "delphi_edm4hep/EventHeaderObj.h"
#include "delphi_edm4hep/EventHeaderData.h"
#include "delphi_edm4hep/EventHeaderCollection.h"


#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
#include "nlohmann/json.hpp"
#endif

#include <ostream>

namespace delphi {



MutableEventHeader::MutableEventHeader() :
  m_obj(new EventHeaderObj{}, podio::utils::MarkOwned) {}

MutableEventHeader::MutableEventHeader(std::uint32_t eventNumber, std::uint32_t runNumber, std::uint32_t fileNumber, delphi::TimeStamp timeStamp, std::uint32_t delphiDate, std::uint32_t delphiTime) :
  m_obj(new EventHeaderObj{}, podio::utils::MarkOwned) {
  m_obj->data.eventNumber = eventNumber;
  m_obj->data.runNumber = runNumber;
  m_obj->data.fileNumber = fileNumber;
  m_obj->data.timeStamp = timeStamp;
  m_obj->data.delphiDate = delphiDate;
  m_obj->data.delphiTime = delphiTime;
}

MutableEventHeader& MutableEventHeader::operator=(MutableEventHeader other) {
  swap(*this, other);
  return *this;
}

MutableEventHeader MutableEventHeader::clone() const {
  return MutableEventHeader(podio::utils::MaybeSharedPtr(new EventHeaderObj(*m_obj), podio::utils::MarkOwned));
}

MutableEventHeader::MutableEventHeader(podio::utils::MaybeSharedPtr<EventHeaderObj> obj) : m_obj(std::move(obj)) {}
MutableEventHeader::operator EventHeader() const { return EventHeader(m_obj); }

std::uint32_t MutableEventHeader::getEventNumber() const { return m_obj->data.eventNumber; }
std::uint32_t MutableEventHeader::getRunNumber() const { return m_obj->data.runNumber; }
std::uint32_t MutableEventHeader::getFileNumber() const { return m_obj->data.fileNumber; }
const delphi::TimeStamp& MutableEventHeader::getTimeStamp() const { return m_obj->data.timeStamp; }
std::uint32_t MutableEventHeader::getDelphiDate() const { return m_obj->data.delphiDate; }
std::uint32_t MutableEventHeader::getDelphiTime() const { return m_obj->data.delphiTime; }


void MutableEventHeader::setEventNumber(std::uint32_t value) { m_obj->data.eventNumber = value; }
void MutableEventHeader::setRunNumber(std::uint32_t value) { m_obj->data.runNumber = value; }
void MutableEventHeader::setFileNumber(std::uint32_t value) { m_obj->data.fileNumber = value; }
void MutableEventHeader::setTimeStamp(delphi::TimeStamp value) { m_obj->data.timeStamp = value; }
delphi::TimeStamp& MutableEventHeader::timeStamp() { return m_obj->data.timeStamp; }
void MutableEventHeader::setDelphiDate(std::uint32_t value) { m_obj->data.delphiDate = value; }
void MutableEventHeader::setDelphiTime(std::uint32_t value) { m_obj->data.delphiTime = value; }







bool MutableEventHeader::isAvailable() const {
  if (m_obj) {
    return true;
  }
  return false;
}

const podio::ObjectID MutableEventHeader::getObjectID() const {
  if (m_obj) {
    return m_obj->id;
  }
  return podio::ObjectID{};
}

bool MutableEventHeader::operator==(const EventHeader& other) const {
  return m_obj == other.m_obj;
}

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
void to_json(nlohmann::json& j, const MutableEventHeader& value) {
  j = nlohmann::json{
    {"eventNumber", value.getEventNumber()}
    ,{"runNumber", value.getRunNumber()}
    ,{"fileNumber", value.getFileNumber()}
    ,{"timeStamp", value.getTimeStamp()}
    ,{"delphiDate", value.getDelphiDate()}
    ,{"delphiTime", value.getDelphiTime()}
  };


}
#endif


} // namespace delphi

