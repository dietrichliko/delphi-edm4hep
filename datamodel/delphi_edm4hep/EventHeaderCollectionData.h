// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#ifndef DELPHI_EDM4HEP_EventHeader_CollectionData_H
#define DELPHI_EDM4HEP_EventHeader_CollectionData_H

// datamodel specific includes
#include "delphi_edm4hep/EventHeaderData.h"
#include "delphi_edm4hep/EventHeaderObj.h"

// schema evolution specific includes

// podio specific includes
#include "podio/CollectionBuffers.h"
#include "podio/ICollectionProvider.h"

#include <deque>
#include <memory>

namespace delphi {


using EventHeaderObjPointerContainer = std::deque<EventHeaderObj*>;
using EventHeaderDataContainer = std::vector<EventHeaderData>;


/**
 * Class encapsulating everything related to storage of data that is needed by a
 * collection.
 */
class EventHeaderCollectionData {
public:
  /**
   * The Objs of this collection
   */
  EventHeaderObjPointerContainer entries{};

  /**
   * Default constructor setting up the necessary buffers
   */
  EventHeaderCollectionData();

  /**
   * Constructor from existing I/O buffers
   */
  EventHeaderCollectionData(podio::CollectionReadBuffers buffers, bool isSubsetColl);

  /**
   * Non copy-able, move-only class
   */
  EventHeaderCollectionData(const EventHeaderCollectionData&) = delete;
  EventHeaderCollectionData& operator=(const EventHeaderCollectionData&) = delete;
  EventHeaderCollectionData(EventHeaderCollectionData&& other) = default;
  EventHeaderCollectionData& operator=(EventHeaderCollectionData&& other) = default;

  /**
   * Deconstructor
   */
  ~EventHeaderCollectionData() = default;

  void clear(bool isSubsetColl);

  podio::CollectionWriteBuffers getCollectionBuffers(bool isSubsetColl);

  void prepareForWrite(bool isSubsetColl);

  void prepareAfterRead(uint32_t collectionID);

  void makeSubsetCollection();


  bool setReferences(const podio::ICollectionProvider* collectionProvider, bool isSubsetColl);

private:
  // members to handle 1-to-N-relations

  // members to handle vector members

  // I/O related buffers
  podio::CollRefCollection m_refCollections{};
  podio::VectorMembersInfo m_vecmem_info{};
  std::unique_ptr<EventHeaderDataContainer> m_data{nullptr};
};


} // namespace delphi


#endif
