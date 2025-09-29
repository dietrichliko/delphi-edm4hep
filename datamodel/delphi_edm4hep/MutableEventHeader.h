// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#ifndef DELPHI_EDM4HEP_MutableEventHeader_H
#define DELPHI_EDM4HEP_MutableEventHeader_H

#include "delphi_edm4hep/EventHeaderObj.h"
// Make the immutable class available from its mutable version but not vice versa
#include "delphi_edm4hep/EventHeader.h"

#include "delphi_edm4hep/TimeStamp.h"
#include <cstdint>

#include "podio/utilities/MaybeSharedPtr.h"

#include <ostream>
#include <cstddef>

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
#include "nlohmann/json_fwd.hpp"
#endif



namespace delphi {


/** @class MutableEventHeader
 *  DELPHI-specific event header with extended metadata
 *  @author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
 */
class MutableEventHeader {

  friend class EventHeaderCollection;
  friend class EventHeaderMutableCollectionIterator;
  friend class EventHeader;

public:
  using object_type = EventHeader;
  using collection_type = EventHeaderCollection;

  /// default constructor
  MutableEventHeader();

  /// Constructor initializing all members
  MutableEventHeader(std::uint32_t eventNumber, std::uint32_t runNumber, std::uint32_t fileNumber, delphi::TimeStamp timeStamp, std::uint32_t delphiDate, std::uint32_t delphiTime);

  /// copy constructor
  MutableEventHeader(const MutableEventHeader& other) = default;

  /// copy-assignment operator
  MutableEventHeader& operator=(MutableEventHeader other);

  /// create a mutable deep-copy of the object with identical relations
  MutableEventHeader clone() const;

  /// destructor
  ~MutableEventHeader() = default;


  /// conversion to const object
  operator EventHeader() const;

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



  /// Set the Event number within the run
  void setEventNumber(std::uint32_t value);

  /// Set the Run number
  void setRunNumber(std::uint32_t value);

  /// Set the File number within the run
  void setFileNumber(std::uint32_t value);

  /// Set the Event timestamp
  void setTimeStamp(delphi::TimeStamp value);
  /// Get reference to Event timestamp
  delphi::TimeStamp& timeStamp();

  /// Set the Original DELPHI date format (YYMMDD)
  void setDelphiDate(std::uint32_t value);

  /// Set the Original DELPHI time format (HHMMSS)
  void setDelphiTime(std::uint32_t value);






  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from EventHeaderObj instance
  void unlink() { m_obj = podio::utils::MaybeSharedPtr<EventHeaderObj>{nullptr}; }

  bool operator==(const MutableEventHeader& other) const { return m_obj == other.m_obj; }
  bool operator==(const EventHeader& other) const;

  // less comparison operator, so that objects can be e.g. stored in sets.
  bool operator<(const MutableEventHeader& other) const { return m_obj < other.m_obj; }

  podio::ObjectID id() const { return getObjectID(); }

  const podio::ObjectID getObjectID() const;

  friend void swap(MutableEventHeader& a, MutableEventHeader& b) {
    using std::swap;
    swap(a.m_obj, b.m_obj); // swap out the internal pointers
  }

private:
  /// constructor from existing EventHeaderObj
  explicit MutableEventHeader(podio::utils::MaybeSharedPtr<EventHeaderObj> obj);

  podio::utils::MaybeSharedPtr<EventHeaderObj> m_obj{nullptr};
};

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
void to_json(nlohmann::json& j, const MutableEventHeader& value);
#endif


} // namespace delphi


#endif
