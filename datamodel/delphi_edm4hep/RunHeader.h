// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#ifndef DELPHI_EDM4HEP_RunHeader_H
#define DELPHI_EDM4HEP_RunHeader_H

#include "delphi_edm4hep/RunHeaderObj.h"

#include "delphi_edm4hep/Vector3f.h"
#include <cstdint>

#include "podio/utilities/MaybeSharedPtr.h"

#include <ostream>
#include <cstddef>

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
#include "nlohmann/json_fwd.hpp"
#endif



namespace delphi {

class MutableRunHeader;
class RunHeaderCollection;
class RunHeaderCollectionData;

/** @class RunHeader
 *  DELPHI-specific run header information
 *  @author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
 */
class RunHeader {

  friend class MutableRunHeader;
  friend class RunHeaderCollection;
  friend class delphi::RunHeaderCollectionData;
  friend class RunHeaderCollectionIterator;

public:
  using mutable_type = MutableRunHeader;
  using collection_type = RunHeaderCollection;

  /// default constructor
  RunHeader();

  /// Constructor initializing all members
  RunHeader(std::uint32_t experimentNumber, std::uint32_t runNumber, std::uint32_t fileNumber, std::uint32_t fillNumber, std::uint32_t startTime, std::uint32_t endTime, float beamEnergy, delphi::Vector3f beamSpot);

  /// copy constructor
  RunHeader(const RunHeader& other) = default;

  /// copy-assignment operator
  RunHeader& operator=(RunHeader other);

  /// create a mutable deep-copy of the object with identical relations
  MutableRunHeader clone() const;

  /// destructor
  ~RunHeader() = default;


  static RunHeader makeEmpty();

public:

  /// Access the Experiment number (always 1000 for DELPHI)
  std::uint32_t getExperimentNumber() const;

  /// Access the Run number
  std::uint32_t getRunNumber() const;

  /// Access the File number within the run
  std::uint32_t getFileNumber() const;

  /// Access the LEP fill number
  std::uint32_t getFillNumber() const;

  /// Access the Run start time (Unix timestamp)
  std::uint32_t getStartTime() const;

  /// Access the Run end time (Unix timestamp)
  std::uint32_t getEndTime() const;

  /// Access the LEP beam energy in GeV
  float getBeamEnergy() const;

  /// Access the Beam spot position
  const delphi::Vector3f& getBeamSpot() const;





  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from RunHeaderObj instance
  void unlink() { m_obj = podio::utils::MaybeSharedPtr<RunHeaderObj>{nullptr}; }

  bool operator==(const RunHeader& other) const { return m_obj == other.m_obj; }
  bool operator==(const MutableRunHeader& other) const;

  // less comparison operator, so that objects can be e.g. stored in sets.
  bool operator<(const RunHeader& other) const { return m_obj < other.m_obj; }

  podio::ObjectID id() const { return getObjectID(); }

  const podio::ObjectID getObjectID() const;

  friend void swap(RunHeader& a, RunHeader& b) {
    using std::swap;
    swap(a.m_obj, b.m_obj); // swap out the internal pointers
  }

private:
  /// constructor from existing RunHeaderObj
  explicit RunHeader(podio::utils::MaybeSharedPtr<RunHeaderObj> obj);
  RunHeader(RunHeaderObj* obj);

  podio::utils::MaybeSharedPtr<RunHeaderObj> m_obj{nullptr};
};

std::ostream& operator<<(std::ostream& o, const RunHeader& value);

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
void to_json(nlohmann::json& j, const RunHeader& value);
#endif


} // namespace delphi


#endif
