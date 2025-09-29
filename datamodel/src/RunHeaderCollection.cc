// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#include "podio/CollectionBufferFactory.h"
#include "podio/SchemaEvolution.h"

#include "delphi_edm4hep/RunHeaderCollection.h"
#include "delphi_edm4hep/DatamodelDefinition.h"



#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
#include "nlohmann/json.hpp"
#endif

// standard includes
#include <stdexcept>
#include <iomanip>

namespace delphi {


RunHeaderCollection::RunHeaderCollection() :
  m_isValid(false), m_isPrepared(false), m_isSubsetColl(false), m_collectionID(podio::ObjectID::untracked), m_storageMtx(std::make_unique<std::mutex>()), m_storage() {}

RunHeaderCollection::RunHeaderCollection(RunHeaderCollectionData&& data, bool isSubsetColl) :
  m_isValid(false), m_isPrepared(false), m_isSubsetColl(isSubsetColl), m_collectionID(podio::ObjectID::untracked), m_storageMtx(std::make_unique<std::mutex>()), m_storage(std::move(data)) {}

RunHeaderCollection::~RunHeaderCollection() {
  // Need to tell the storage how to clean-up
  m_storage.clear(m_isSubsetColl);
}

RunHeader RunHeaderCollection::operator[](std::size_t index) const {
  return RunHeader(m_storage.entries[index]);
}

RunHeader RunHeaderCollection::at(std::size_t index) const {
  return RunHeader(m_storage.entries.at(index));
}

MutableRunHeader RunHeaderCollection::operator[](std::size_t index) {
  return MutableRunHeader(podio::utils::MaybeSharedPtr(m_storage.entries[index]));
}

MutableRunHeader RunHeaderCollection::at(std::size_t index) {
  return MutableRunHeader(podio::utils::MaybeSharedPtr(m_storage.entries.at(index)));
}

std::size_t RunHeaderCollection::size() const {
  return m_storage.entries.size();
}

bool RunHeaderCollection::empty() const {
  return m_storage.entries.empty();
}

void RunHeaderCollection::setSubsetCollection(bool setSubset) {
  if (m_isSubsetColl != setSubset && !m_storage.entries.empty()) {
    throw std::logic_error("Cannot change the character of a collection that already contains elements");
  }

  if (setSubset) {
    m_storage.makeSubsetCollection();
  }
  m_isSubsetColl = setSubset;
}

MutableRunHeader RunHeaderCollection::create() {
  if (m_isSubsetColl) {
    throw std::logic_error("Cannot create new elements on a subset collection");
  }

  auto obj = m_storage.entries.emplace_back(new RunHeaderObj());

  obj->id = {int(m_storage.entries.size() - 1), m_collectionID};
  return MutableRunHeader(podio::utils::MaybeSharedPtr(obj));
}

void RunHeaderCollection::clear() {
  m_storage.clear(m_isSubsetColl);
  m_isPrepared = false;
}

void RunHeaderCollection::prepareForWrite() const {
  // TODO: Replace this double locking pattern here with an atomic and only one
  // lock. Problem: std::atomic is not default movable.
  {
    std::lock_guard lock{*m_storageMtx};
    // If the collection has been prepared already there is nothing to do
    if (m_isPrepared) {
      return;
    }
  }

  std::lock_guard lock{*m_storageMtx};
  // by the time we acquire the lock another thread might have already
  // succeeded, so we need to check again now
  if (m_isPrepared) {
    return;
  }
  m_storage.prepareForWrite(m_isSubsetColl);
  m_isPrepared = true;
}

void RunHeaderCollection::prepareAfterRead() {
  // No need to go through this again if we have already done it
  if (m_isPrepared) {
    return;
  }

  if (!m_isSubsetColl) {
    // Subset collections do not store any data that would require post-processing
    m_storage.prepareAfterRead(m_collectionID);
  }
  // Preparing a collection doesn't affect the underlying I/O buffers, so this
  // collection is still prepared
  m_isPrepared = true;
}

bool RunHeaderCollection::setReferences(const podio::ICollectionProvider* collectionProvider) {
  return m_storage.setReferences(collectionProvider, m_isSubsetColl);
}

void RunHeaderCollection::push_back(MutableRunHeader object) {
  // We have to do different things here depending on whether this is a
  // subset collection or not. A normal collection cannot collect objects
  // that are already part of another collection, while a subset collection
  // can only collect such objects
  if (!m_isSubsetColl) {
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
      const auto size = m_storage.entries.size();
      obj->id = {(int)size, m_collectionID};
      m_storage.entries.push_back(obj.release());
    } else {
      throw std::invalid_argument("Object already in a collection. Cannot add it to a second collection");
    }
  } else {

    push_back(RunHeader(object));
  }
}

void RunHeaderCollection::push_back(RunHeader object) {
  if (!m_isSubsetColl) {
    throw std::invalid_argument("Can only add immutable objects to subset collections");
  }
  auto obj = object.m_obj;
  if (obj->id.index < 0) {
    // This path is only possible if we arrive here from an untracked Mutable object
    throw std::invalid_argument("Object needs to be tracked by another collection in order for it to be storable in a subset collection");
  }
  m_storage.entries.push_back(obj.release());
}

podio::CollectionWriteBuffers RunHeaderCollection::getBuffers() {
  return m_storage.getCollectionBuffers(m_isSubsetColl);
}

std::vector<std::uint32_t> RunHeaderCollection::experimentNumber(const size_t nElem) const {
  std::vector<std::uint32_t> tmp;
  const auto valid_size = nElem != 0 ? std::min(nElem, m_storage.entries.size()) : m_storage.entries.size();
  tmp.reserve(valid_size);
  for (size_t i = 0; i < valid_size; ++i) {
    tmp.emplace_back(m_storage.entries[i]->data.experimentNumber);
  }
  return tmp;
}

std::vector<std::uint32_t> RunHeaderCollection::runNumber(const size_t nElem) const {
  std::vector<std::uint32_t> tmp;
  const auto valid_size = nElem != 0 ? std::min(nElem, m_storage.entries.size()) : m_storage.entries.size();
  tmp.reserve(valid_size);
  for (size_t i = 0; i < valid_size; ++i) {
    tmp.emplace_back(m_storage.entries[i]->data.runNumber);
  }
  return tmp;
}

std::vector<std::uint32_t> RunHeaderCollection::fileNumber(const size_t nElem) const {
  std::vector<std::uint32_t> tmp;
  const auto valid_size = nElem != 0 ? std::min(nElem, m_storage.entries.size()) : m_storage.entries.size();
  tmp.reserve(valid_size);
  for (size_t i = 0; i < valid_size; ++i) {
    tmp.emplace_back(m_storage.entries[i]->data.fileNumber);
  }
  return tmp;
}

std::vector<std::uint32_t> RunHeaderCollection::fillNumber(const size_t nElem) const {
  std::vector<std::uint32_t> tmp;
  const auto valid_size = nElem != 0 ? std::min(nElem, m_storage.entries.size()) : m_storage.entries.size();
  tmp.reserve(valid_size);
  for (size_t i = 0; i < valid_size; ++i) {
    tmp.emplace_back(m_storage.entries[i]->data.fillNumber);
  }
  return tmp;
}

std::vector<std::uint32_t> RunHeaderCollection::startTime(const size_t nElem) const {
  std::vector<std::uint32_t> tmp;
  const auto valid_size = nElem != 0 ? std::min(nElem, m_storage.entries.size()) : m_storage.entries.size();
  tmp.reserve(valid_size);
  for (size_t i = 0; i < valid_size; ++i) {
    tmp.emplace_back(m_storage.entries[i]->data.startTime);
  }
  return tmp;
}

std::vector<std::uint32_t> RunHeaderCollection::endTime(const size_t nElem) const {
  std::vector<std::uint32_t> tmp;
  const auto valid_size = nElem != 0 ? std::min(nElem, m_storage.entries.size()) : m_storage.entries.size();
  tmp.reserve(valid_size);
  for (size_t i = 0; i < valid_size; ++i) {
    tmp.emplace_back(m_storage.entries[i]->data.endTime);
  }
  return tmp;
}

std::vector<float> RunHeaderCollection::beamEnergy(const size_t nElem) const {
  std::vector<float> tmp;
  const auto valid_size = nElem != 0 ? std::min(nElem, m_storage.entries.size()) : m_storage.entries.size();
  tmp.reserve(valid_size);
  for (size_t i = 0; i < valid_size; ++i) {
    tmp.emplace_back(m_storage.entries[i]->data.beamEnergy);
  }
  return tmp;
}

std::vector<delphi::Vector3f> RunHeaderCollection::beamSpot(const size_t nElem) const {
  std::vector<delphi::Vector3f> tmp;
  const auto valid_size = nElem != 0 ? std::min(nElem, m_storage.entries.size()) : m_storage.entries.size();
  tmp.reserve(valid_size);
  for (size_t i = 0; i < valid_size; ++i) {
    tmp.emplace_back(m_storage.entries[i]->data.beamSpot);
  }
  return tmp;
}


size_t RunHeaderCollection::getDatamodelRegistryIndex() const {
  return delphi_edm4hep::meta::DatamodelRegistryIndex::value();
}

podio::SchemaVersionT RunHeaderCollection::getSchemaVersion() const {
  return delphi_edm4hep::meta::schemaVersion;
}

// anonymous namespace for registration with the CollectionBufferFactory. This
// ensures that we don't have to make up arbitrary namespace names here, since
// none of this is publicly visible
namespace {
 
podio::CollectionReadBuffers createBuffers(bool isSubset) {
  auto readBuffers = podio::CollectionReadBuffers{};
  readBuffers.type = "delphi::RunHeaderCollection";
  readBuffers.schemaVersion = delphi_edm4hep::meta::schemaVersion;
  readBuffers.data = isSubset ? nullptr : new RunHeaderDataContainer;
  // The number of ObjectID vectors is either 1 or the sum of OneToMany and
  // OneToOne relations
  const auto nRefs = isSubset ? 1 : 0 + 0;
  readBuffers.references = new podio::CollRefCollection(nRefs);
  for (auto& ref : *readBuffers.references) {
    // Make sure to place usable buffer pointers here
    ref = std::make_unique<std::vector<podio::ObjectID>>();
  }

  readBuffers.vectorMembers = new podio::VectorMembersInfo();
  if (!isSubset) {
    readBuffers.vectorMembers->reserve(0);
  }

  readBuffers.createCollection = [](podio::CollectionReadBuffers buffers, bool isSubsetColl) {
    RunHeaderCollectionData data(buffers, isSubsetColl);
    return std::make_unique<RunHeaderCollection>(std::move(data), isSubsetColl);
  };

  readBuffers.recast = [](podio::CollectionReadBuffers& buffers) {
    // We only have any of these buffers if this is not a subset collection
    if (buffers.data) {
      buffers.data = podio::CollectionWriteBuffers::asVector<delphi::RunHeaderData>(buffers.data);
    }
  };

  readBuffers.deleteBuffers = [](podio::CollectionReadBuffers& buffers) {
    if (buffers.data) {
      // If we have data then we are not a subset collection and we have to
      // clean up all type erased buffers by casting them back to something that
      // we can delete
      delete static_cast<delphi::RunHeaderDataContainer*>(buffers.data);

    }
    delete buffers.references;
    delete buffers.vectorMembers;
  };

  return readBuffers;
}




// The usual trick with an IIFE and a static variable inside a funtion and then
// making sure to call that function during shared library loading
bool registerCollection() {
  const static auto reg = []() {
    auto& factory = podio::CollectionBufferFactory::mutInstance();
    factory.registerCreationFunc("delphi::RunHeaderCollection", delphi_edm4hep::meta::schemaVersion, createBuffers);

    // Make the SchemaEvolution aware of the current version by
    // registering a no-op function for this and all preceeding versions
    // will be overriden whenever an explicit action is required
    for (unsigned int schemaVersion=1; schemaVersion< delphi_edm4hep::meta::schemaVersion+1; ++schemaVersion) {
      podio::SchemaEvolution::mutInstance().registerEvolutionFunc(
        "delphi::RunHeaderCollection",
        schemaVersion,
        delphi_edm4hep::meta::schemaVersion,
        podio::SchemaEvolution::noOpSchemaEvolution,
        podio::SchemaEvolution::Priority::AutoGenerated
      );
    }


    return true;
  }();
  return reg;
}

const auto registeredCollection = registerCollection();
} // namespace


#if defined(PODIO_JSON_OUTPUT) && !defined(__CLING__)
void to_json(nlohmann::json& j, const RunHeaderCollection& collection) {
  j = nlohmann::json::array();
  for (auto&& elem : collection) {
    j.emplace_back(elem);
  }
}
#endif


RunHeader RunHeaderCollectionIterator::operator*() {
  m_object.m_obj = podio::utils::MaybeSharedPtr<RunHeaderObj>((*m_collection)[m_index]);
  return m_object;
}

RunHeader* RunHeaderCollectionIterator::operator->() {
  m_object.m_obj = podio::utils::MaybeSharedPtr<RunHeaderObj>((*m_collection)[m_index]);
  return &m_object;
}

RunHeaderCollectionIterator& RunHeaderCollectionIterator::operator++() {
  ++m_index;
  return *this;
}



MutableRunHeader RunHeaderMutableCollectionIterator::operator*() {
  m_object.m_obj = podio::utils::MaybeSharedPtr<RunHeaderObj>((*m_collection)[m_index]);
  return m_object;
}

MutableRunHeader* RunHeaderMutableCollectionIterator::operator->() {
  m_object.m_obj = podio::utils::MaybeSharedPtr<RunHeaderObj>((*m_collection)[m_index]);
  return &m_object;
}

RunHeaderMutableCollectionIterator& RunHeaderMutableCollectionIterator::operator++() {
  ++m_index;
  return *this;
}



std::ostream& operator<<(std::ostream& o, const RunHeaderCollection& v) {
  const auto old_flags = o.flags();
  o << "          id:experimentNumber:   runNumber:  fileNumber:  fillNumber:   startTime:     endTime:  beamEnergy:                 beamSpot [ x, y, z]:" << '\n';

  for (const auto&& el : v) {
    o << std::scientific << std::showpos << std::setw(12) << el.id() << " "
      << std::setw(12) << el.getExperimentNumber() << " "
      << std::setw(12) << el.getRunNumber() << " "
      << std::setw(12) << el.getFileNumber() << " "
      << std::setw(12) << el.getFillNumber() << " "
      << std::setw(12) << el.getStartTime() << " "
      << std::setw(12) << el.getEndTime() << " "
      << std::setw(12) << el.getBeamEnergy() << " "
      << std::setw(12) << el.getBeamSpot() << " "
      << std::endl;




  }

  o.flags(old_flags);
  return o;
}

void RunHeaderCollection::print(std::ostream& os, bool flush) const {
  os << *this;
  if (flush) {
    os.flush();
  }
}


} // namespace delphi

