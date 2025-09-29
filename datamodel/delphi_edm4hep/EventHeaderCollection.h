// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#ifndef DELPHI_EDM4HEP_EventHeaderCollection_H
#define DELPHI_EDM4HEP_EventHeaderCollection_H

// datamodel specific includes
#include "delphi_edm4hep/EventHeaderData.h"
#include "delphi_edm4hep/EventHeader.h"
#include "delphi_edm4hep/MutableEventHeader.h"
#include "delphi_edm4hep/EventHeaderObj.h"
#include "delphi_edm4hep/EventHeaderCollectionData.h"

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
#include "nlohmann/json_fwd.hpp"
#endif

#include <string>
#include <vector>
#include <deque>
#include <array>
#include <algorithm>
#include <ostream>
#include <mutex>
#include <memory>
#include <cstddef>

namespace podio {
  struct RelationNames;
}

namespace delphi {



class EventHeaderCollectionIterator {
public:
  EventHeaderCollectionIterator(size_t index, const EventHeaderObjPointerContainer* collection) : m_index(index), m_object(podio::utils::MaybeSharedPtr<EventHeaderObj>{nullptr}), m_collection(collection) {}

  EventHeaderCollectionIterator(const EventHeaderCollectionIterator&) = delete;
  EventHeaderCollectionIterator& operator=(const EventHeaderCollectionIterator&) = delete;

  bool operator!=(const EventHeaderCollectionIterator& x) const {
    return m_index != x.m_index; // TODO: may not be complete
  }

  bool operator==(const EventHeaderCollectionIterator& x) const {
    return m_index ==  x.m_index; // TODO: may not be complete
  }

  EventHeader operator*();
  EventHeader* operator->();
  EventHeaderCollectionIterator& operator++();

private:
  size_t m_index;
  EventHeader m_object;
  const EventHeaderObjPointerContainer* m_collection;
};


class EventHeaderMutableCollectionIterator {
public:
  EventHeaderMutableCollectionIterator(size_t index, const EventHeaderObjPointerContainer* collection) : m_index(index), m_object(podio::utils::MaybeSharedPtr<EventHeaderObj>{nullptr}), m_collection(collection) {}

  EventHeaderMutableCollectionIterator(const EventHeaderMutableCollectionIterator&) = delete;
  EventHeaderMutableCollectionIterator& operator=(const EventHeaderMutableCollectionIterator&) = delete;

  bool operator!=(const EventHeaderMutableCollectionIterator& x) const {
    return m_index != x.m_index; // TODO: may not be complete
  }

  bool operator==(const EventHeaderMutableCollectionIterator& x) const {
    return m_index ==  x.m_index; // TODO: may not be complete
  }

  MutableEventHeader operator*();
  MutableEventHeader* operator->();
  EventHeaderMutableCollectionIterator& operator++();

private:
  size_t m_index;
  MutableEventHeader m_object;
  const EventHeaderObjPointerContainer* m_collection;
};


/**
A Collection is identified by an ID.
*/
class EventHeaderCollection : public podio::CollectionBase {
public:
  using value_type = EventHeader;
  using const_iterator = EventHeaderCollectionIterator;
  using iterator = EventHeaderMutableCollectionIterator;

  EventHeaderCollection();
  EventHeaderCollection(EventHeaderCollectionData&& data, bool isSubsetColl);
  // This is a move-only type
  EventHeaderCollection(const EventHeaderCollection& ) = delete;
  EventHeaderCollection& operator=(const EventHeaderCollection& ) = delete;
  EventHeaderCollection(EventHeaderCollection&&) = default;
  EventHeaderCollection& operator=(EventHeaderCollection&&) = default;

//  EventHeaderCollection(EventHeaderVector* data, uint32_t collectionID);
  ~EventHeaderCollection();

  constexpr static auto typeName = "delphi::EventHeaderCollection";
  constexpr static auto valueTypeName = "delphi::EventHeader";
  constexpr static auto dataTypeName = "delphi::EventHeaderData";

  void clear() final;

  /// Print this collection to the passed stream
  void print(std::ostream& os=std::cout, bool flush=true) const final;

  /// operator to allow pointer like calling of members a la LCIO
  EventHeaderCollection* operator->() { return (EventHeaderCollection*) this; }

  /// Append a new object to the collection, and return this object.
  MutableEventHeader create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  MutableEventHeader create(Args&&... args);

  /// number of elements in the collection
  std::size_t size() const final;

  /// Is the collection empty
  bool empty() const final;

  /// fully qualified type name
  const std::string_view getTypeName() const final { return typeName; }
  /// fully qualified type name of elements - with namespace
  const std::string_view getValueTypeName() const final { return valueTypeName; }
  /// fully qualified type name of stored POD elements - with namespace
  const std::string_view getDataTypeName() const final { return dataTypeName; }
  /// schema version
  podio::SchemaVersionT getSchemaVersion() const final;

  bool isSubsetCollection() const final {
    return m_isSubsetColl;
  }

  void setSubsetCollection(bool setSubset=true) final;

  /// Returns the const object of given index
  EventHeader operator[](std::size_t index) const;
  /// Returns the object of a given index
  MutableEventHeader operator[](std::size_t index);
  /// Returns the const object of given index
  EventHeader at(std::size_t index) const;
  /// Returns the object of given index
  MutableEventHeader at(std::size_t index);


  /// Append object to the collection
  void push_back(MutableEventHeader object);
  /// Append an object to the (subset) collection
  void push_back(EventHeader object);

  void prepareForWrite() const final;
  void prepareAfterRead() final;
  bool setReferences(const podio::ICollectionProvider* collectionProvider) final;

  /// Get the collection buffers for this collection
  podio::CollectionWriteBuffers getBuffers() final;

  void setID(uint32_t ID) final {
    m_collectionID = ID;
    if (!m_isSubsetColl) {
      std::for_each(m_storage.entries.begin(), m_storage.entries.end(),
                  [ID] (EventHeaderObj* obj) { obj->id = {obj->id.index, static_cast<uint32_t>(ID)}; }
      );
    }
    m_isValid = true;
  };

  uint32_t getID() const final {
    return m_collectionID;
  }

  bool isValid() const final {
    return m_isValid;
  }

  size_t getDatamodelRegistryIndex() const final;

  // support for the iterator protocol
  iterator begin() {
    return iterator(0, &m_storage.entries);
  }
  const_iterator begin() const {
    return const_iterator(0, &m_storage.entries);
  }
  iterator end() {
    return iterator(m_storage.entries.size(), &m_storage.entries);
  }
  const_iterator end() const {
    return const_iterator(m_storage.entries.size(), &m_storage.entries);
  }

  std::vector<std::uint32_t> eventNumber(const size_t nElem = 0) const;
  std::vector<std::uint32_t> runNumber(const size_t nElem = 0) const;
  std::vector<std::uint32_t> fileNumber(const size_t nElem = 0) const;
  std::vector<delphi::TimeStamp> timeStamp(const size_t nElem = 0) const;
  std::vector<std::uint32_t> delphiDate(const size_t nElem = 0) const;
  std::vector<std::uint32_t> delphiTime(const size_t nElem = 0) const;

private:
  // For setReferences, we need to give our own CollectionData access to our
  // private entries. Otherwise we would need to expose a public member function
  // that gives access to the Obj* which is definitely not what we want
  friend class EventHeaderCollectionData;

  bool m_isValid{false};
  mutable bool m_isPrepared{false};
  bool m_isSubsetColl{false};
  uint32_t m_collectionID{0};
  mutable std::unique_ptr<std::mutex> m_storageMtx{nullptr};
  mutable EventHeaderCollectionData m_storage{};
};

std::ostream& operator<<(std::ostream& o, const EventHeaderCollection& v);

template<typename... Args>
MutableEventHeader EventHeaderCollection::create(Args&&... args) {
  if (m_isSubsetColl) {
    throw std::logic_error("Cannot create new elements on a subset collection");
  }
  const int size = m_storage.entries.size();
  auto obj = new EventHeaderObj({size, m_collectionID}, {std::forward<Args>(args)...});
  m_storage.entries.push_back(obj);

  return MutableEventHeader(podio::utils::MaybeSharedPtr(obj));
}

#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
void to_json(nlohmann::json& j, const EventHeaderCollection& collection);
#endif

} // namespace delphi


#endif
