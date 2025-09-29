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



EventHeader::EventHeader() :
  m_obj(new EventHeaderObj{}, podio::utils::MarkOwned) {}

EventHeader::EventHeader(std::uint32_t eventNumber, std::uint32_t runNumber, std::uint32_t fileNumber, delphi::TimeStamp timeStamp, std::uint32_t delphiDate, std::uint32_t delphiTime) :
  m_obj(new EventHeaderObj{}, podio::utils::MarkOwned) {
  m_obj->data.eventNumber = eventNumber;
  m_obj->data.runNumber = runNumber;
  m_obj->data.fileNumber = fileNumber;
  m_obj->data.timeStamp = timeStamp;
  m_obj->data.delphiDate = delphiDate;
  m_obj->data.delphiTime = delphiTime;
}

EventHeader& EventHeader::operator=(EventHeader other) {
  swap(*this, other);
  return *this;
}

MutableEventHeader EventHeader::clone() const {
  return MutableEventHeader(podio::utils::MaybeSharedPtr(new EventHeaderObj(*m_obj), podio::utils::MarkOwned));
}

EventHeader::EventHeader(podio::utils::MaybeSharedPtr<EventHeaderObj> obj) : m_obj(std::move(obj)) {}

EventHeader::EventHeader(EventHeaderObj* obj) : m_obj(podio::utils::MaybeSharedPtr<EventHeaderObj>(obj)) {}

EventHeader EventHeader::makeEmpty() {
  return {nullptr};
}

std::uint32_t EventHeader::getEventNumber() const { return m_obj->data.eventNumber; }
std::uint32_t EventHeader::getRunNumber() const { return m_obj->data.runNumber; }
std::uint32_t EventHeader::getFileNumber() const { return m_obj->data.fileNumber; }
const delphi::TimeStamp& EventHeader::getTimeStamp() const { return m_obj->data.timeStamp; }
std::uint32_t EventHeader::getDelphiDate() const { return m_obj->data.delphiDate; }
std::uint32_t EventHeader::getDelphiTime() const { return m_obj->data.delphiTime; }






bool EventHeader::isAvailable() const {
  if (m_obj) {
    return true;
  }
  return false;
}

const podio::ObjectID EventHeader::getObjectID() const {
  if (m_obj) {
    return m_obj->id;
  }
  return podio::ObjectID{};
}

bool EventHeader::operator==(const MutableEventHeader& other) const {
  return m_obj == other.m_obj;
}

std::ostream& operator<<(std::ostream& o, const EventHeader& value) {
  if (!value.isAvailable()) {
    return o << "[not available]";
  }
  o << " id: " << value.id() << '\n';
  o << " eventNumber : " << value.getEventNumber() << '\n';
  o << " runNumber : " << value.getRunNumber() << '\n';
  o << " fileNumber : " << value.getFileNumber() << '\n';
  o << " timeStamp : " << value.getTimeStamp() << '\n';
  o << " delphiDate : " << value.getDelphiDate() << '\n';
  o << " delphiTime : " << value.getDelphiTime() << '\n';



  return o;
}

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
void to_json(nlohmann::json& j, const EventHeader& value) {
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

