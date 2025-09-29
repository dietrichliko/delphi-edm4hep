// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#ifndef DELPHI_EDM4HEP_RunHeader_CollectionData_H
#define DELPHI_EDM4HEP_RunHeader_CollectionData_H

// datamodel specific includes
#include "delphi_edm4hep/RunHeaderData.h"
#include "delphi_edm4hep/RunHeaderObj.h"

// schema evolution specific includes

// podio specific includes
#include "podio/CollectionBuffers.h"
#include "podio/ICollectionProvider.h"

#include <deque>
#include <memory>

namespace delphi {


using RunHeaderObjPointerContainer = std::deque<RunHeaderObj*>;
using RunHeaderDataContainer = std::vector<RunHeaderData>;


/**
 * Class encapsulating everything related to storage of data that is needed by a
 * collection.
 */
class RunHeaderCollectionData {
public:
  /**
   * The Objs of this collection
   */
  RunHeaderObjPointerContainer entries{};

  /**
   * Default constructor setting up the necessary buffers
   */
  RunHeaderCollectionData();

  /**
   * Constructor from existing I/O buffers
   */
  RunHeaderCollectionData(podio::CollectionReadBuffers buffers, bool isSubsetColl);

  /**
   * Non copy-able, move-only class
   */
  RunHeaderCollectionData(const RunHeaderCollectionData&) = delete;
  RunHeaderCollectionData& operator=(const RunHeaderCollectionData&) = delete;
  RunHeaderCollectionData(RunHeaderCollectionData&& other) = default;
  RunHeaderCollectionData& operator=(RunHeaderCollectionData&& other) = default;

  /**
   * Deconstructor
   */
  ~RunHeaderCollectionData() = default;

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
  std::unique_ptr<RunHeaderDataContainer> m_data{nullptr};
};


} // namespace delphi


#endif
