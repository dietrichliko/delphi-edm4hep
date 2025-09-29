// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#ifndef DELPHI_EDM4HEP_MutableRunHeader_H
#define DELPHI_EDM4HEP_MutableRunHeader_H

#include "delphi_edm4hep/RunHeaderObj.h"
// Make the immutable class available from its mutable version but not vice versa
#include "delphi_edm4hep/RunHeader.h"

#include "delphi_edm4hep/Vector3f.h"
#include <cstdint>

#include "podio/utilities/MaybeSharedPtr.h"

#include <ostream>
#include <cstddef>

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
#include "nlohmann/json_fwd.hpp"
#endif



namespace delphi {


/** @class MutableRunHeader
 *  DELPHI-specific run header information
 *  @author: Dietrich Liko <Dietrich.Liko@oeaw.ac.at>
 */
class MutableRunHeader {

  friend class RunHeaderCollection;
  friend class RunHeaderMutableCollectionIterator;
  friend class RunHeader;

public:
  using object_type = RunHeader;
  using collection_type = RunHeaderCollection;

  /// default constructor
  MutableRunHeader();

  /// Constructor initializing all members
  MutableRunHeader(std::uint32_t experimentNumber, std::uint32_t runNumber, std::uint32_t fileNumber, std::uint32_t fillNumber, std::uint32_t startTime, std::uint32_t endTime, float beamEnergy, delphi::Vector3f beamSpot);

  /// copy constructor
  MutableRunHeader(const MutableRunHeader& other) = default;

  /// copy-assignment operator
  MutableRunHeader& operator=(MutableRunHeader other);

  /// create a mutable deep-copy of the object with identical relations
  MutableRunHeader clone() const;

  /// destructor
  ~MutableRunHeader() = default;


  /// conversion to const object
  operator RunHeader() const;

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



  /// Set the Experiment number (always 1000 for DELPHI)
  void setExperimentNumber(std::uint32_t value);

  /// Set the Run number
  void setRunNumber(std::uint32_t value);

  /// Set the File number within the run
  void setFileNumber(std::uint32_t value);

  /// Set the LEP fill number
  void setFillNumber(std::uint32_t value);

  /// Set the Run start time (Unix timestamp)
  void setStartTime(std::uint32_t value);

  /// Set the Run end time (Unix timestamp)
  void setEndTime(std::uint32_t value);

  /// Set the LEP beam energy in GeV
  void setBeamEnergy(float value);

  /// Set the Beam spot position
  void setBeamSpot(delphi::Vector3f value);
  /// Get reference to Beam spot position
  delphi::Vector3f& beamSpot();






  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from RunHeaderObj instance
  void unlink() { m_obj = podio::utils::MaybeSharedPtr<RunHeaderObj>{nullptr}; }

  bool operator==(const MutableRunHeader& other) const { return m_obj == other.m_obj; }
  bool operator==(const RunHeader& other) const;

  // less comparison operator, so that objects can be e.g. stored in sets.
  bool operator<(const MutableRunHeader& other) const { return m_obj < other.m_obj; }

  podio::ObjectID id() const { return getObjectID(); }

  const podio::ObjectID getObjectID() const;

  friend void swap(MutableRunHeader& a, MutableRunHeader& b) {
    using std::swap;
    swap(a.m_obj, b.m_obj); // swap out the internal pointers
  }

private:
  /// constructor from existing RunHeaderObj
  explicit MutableRunHeader(podio::utils::MaybeSharedPtr<RunHeaderObj> obj);

  podio::utils::MaybeSharedPtr<RunHeaderObj> m_obj{nullptr};
};

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
void to_json(nlohmann::json& j, const MutableRunHeader& value);
#endif


} // namespace delphi


#endif
