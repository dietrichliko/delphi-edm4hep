// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#ifndef DELPHI_EDM4HEP_EventHeader_H
#define DELPHI_EDM4HEP_EventHeader_H

#include "delphi_edm4hep/EventHeaderObj.h"

#include "delphi_edm4hep/TimeStamp.h"
#include <cstdint>

#include "podio/utilities/MaybeSharedPtr.h"

#include <ostream>
#include <cstddef>

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
#include "nlohmann/json_fwd.hpp"
#endif



namespace delphi {

class MutableEventHeader;
class EventHeaderCollection;
class EventHeaderCollectionData;

/** @class EventHeader
 *  DELPHI-specific event header with extended metadata
 *  @author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
 */
class EventHeader {

  friend class MutableEventHeader;
  friend class EventHeaderCollection;
  friend class delphi::EventHeaderCollectionData;
  friend class EventHeaderCollectionIterator;

public:
  using mutable_type = MutableEventHeader;
  using collection_type = EventHeaderCollection;

  /// default constructor
  EventHeader();

  /// Constructor initializing all members
  EventHeader(std::uint32_t eventNumber, std::uint32_t runNumber, std::uint32_t fileNumber, delphi::TimeStamp timeStamp, std::uint32_t delphiDate, std::uint32_t delphiTime);

  /// copy constructor
  EventHeader(const EventHeader& other) = default;

  /// copy-assignment operator
  EventHeader& operator=(EventHeader other);

  /// create a mutable deep-copy of the object with identical relations
  MutableEventHeader clone() const;

  /// destructor
  ~EventHeader() = default;


  static EventHeader makeEmpty();

public:

  /// Access the Event number within the run
  std::uint32_t getEventNumber() const;

  /// Access the Run number
  std::uint32_t getRunNumber() const;

  /// Access the File number within the run
  std::uint32_t getFileNumber() const;

  /// Access the Event timestamp
  const delphi::TimeStamp& getTimeStamp() const;

  /// Access the Original DELPHI date format (YYMMDD)
  std::uint32_t getDelphiDate() const;

  /// Access the Original DELPHI time format (HHMMSS)
  std::uint32_t getDelphiTime() const;





  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from EventHeaderObj instance
  void unlink() { m_obj = podio::utils::MaybeSharedPtr<EventHeaderObj>{nullptr}; }

  bool operator==(const EventHeader& other) const { return m_obj == other.m_obj; }
  bool operator==(const MutableEventHeader& other) const;

  // less comparison operator, so that objects can be e.g. stored in sets.
  bool operator<(const EventHeader& other) const { return m_obj < other.m_obj; }

  podio::ObjectID id() const { return getObjectID(); }

  const podio::ObjectID getObjectID() const;

  friend void swap(EventHeader& a, EventHeader& b) {
    using std::swap;
    swap(a.m_obj, b.m_obj); // swap out the internal pointers
  }

private:
  /// constructor from existing EventHeaderObj
  explicit EventHeader(podio::utils::MaybeSharedPtr<EventHeaderObj> obj);
  EventHeader(EventHeaderObj* obj);

  podio::utils::MaybeSharedPtr<EventHeaderObj> m_obj{nullptr};
};

std::ostream& operator<<(std::ostream& o, const EventHeader& value);

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
void to_json(nlohmann::json& j, const EventHeader& value);
#endif


} // namespace delphi


#endif
