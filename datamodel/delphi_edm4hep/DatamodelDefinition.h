// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#include "podio/DatamodelRegistry.h"
#include "podio/SchemaEvolution.h"

namespace delphi_edm4hep::meta {
/**
 * The complete definition of the datamodel at generation time in JSON format.
 */
static constexpr auto delphi_edm4hep__JSONDefinition = R"DATAMODELDEF({"options": {"getSyntax": true, "exposePODMembers": false, "includeSubfolder": "delphi_edm4hep/"}, "schema_version": 1, "components": {"delphi::Vector3f": {"Members": ["float x", "float y", "float z"], "ExtraCode": {"declaration": "constexpr Vector3f() : x(0),y(0),z(0) {}\nconstexpr Vector3f(float xx, float yy, float zz) : x(xx),y(yy),z(zz) {}\nconstexpr Vector3f(const float* v) : x(v[0]),y(v[1]),z(v[2]) {}\nconstexpr bool operator==(const Vector3f& v) const { return (x==v.x&&y==v.y&&z==v.z) ; }\nconstexpr float operator[](unsigned i) const { return *( &x + i ) ; }\n"}}, "delphi::TimeStamp": {"Members": ["std::uint64_t unixTime // Unix timestamp in seconds since epoch"]}}, "datatypes": {"delphi::EventHeader": {"Description": "DELPHI-specific event header with extended metadata", "Author": "Dietrich Liko <Dietrich.Liko@oeaw.ac.at>", "Members": ["std::uint32_t eventNumber // Event number within the run", "std::uint32_t runNumber // Run number", "std::uint32_t fileNumber // File number within the run", "delphi::TimeStamp timeStamp // Event timestamp", "std::uint32_t delphiDate // Original DELPHI date format (YYMMDD)", "std::uint32_t delphiTime // Original DELPHI time format (HHMMSS)"], "VectorMembers": [], "OneToOneRelations": [], "OneToManyRelations": [], "ExtraCode": {}, "MutableExtraCode": {}}, "delphi::RunHeader": {"Description": "DELPHI-specific run header information", "Author": "Dietrich Liko <Dietrich.Liko@oeaw.ac.at>", "Members": ["std::uint32_t experimentNumber // Experiment number (always 1000 for DELPHI)", "std::uint32_t runNumber // Run number", "std::uint32_t fileNumber // File number within the run", "std::uint32_t fillNumber // LEP fill number", "std::uint32_t startTime // Run start time (Unix timestamp)", "std::uint32_t endTime // Run end time (Unix timestamp)", "float beamEnergy // LEP beam energy in GeV", "delphi::Vector3f beamSpot // Beam spot position"], "VectorMembers": [], "OneToOneRelations": [], "OneToManyRelations": [], "ExtraCode": {}, "MutableExtraCode": {}}}, "interfaces": {}})DATAMODELDEF";


/**
 * The names of all relations and vector members for all datatypes
 */
inline podio::RelationNameMapping delphi_edm4hep__getRelationNames() {
  using namespace std::string_view_literals;
  return {
    {"delphi::EventHeader"sv,
      {  },
      {  },
    },
    {"delphi::RunHeader"sv,
      {  },
      {  },
    },
  };
}

/**
 * The schema version at generation time
 */
static constexpr podio::SchemaVersionT schemaVersion = 1;

/**
 * The helper class that takes care of registering the datamodel definition to
 * the DatamodelRegistry and to provide the index in that registry.
 *
 * Implemented as a singleton mainly to ensure only a single registration of
 * each datamodel, during the constructor
 */
class DatamodelRegistryIndex {
public:
  static size_t value() {
    static const auto relationNames = delphi_edm4hep__getRelationNames();
    static auto index = DatamodelRegistryIndex(podio::DatamodelRegistry::mutInstance().registerDatamodel("delphi_edm4hep", delphi_edm4hep__JSONDefinition, relationNames));
    return index.m_value;
  }
private:
  DatamodelRegistryIndex(size_t v) : m_value(v) {}
  size_t m_value{podio::DatamodelRegistry::NoDefinitionAvailable};
};


namespace static_registration {
  // The usual trick via an IIFE and a const variable that we assign to, to
  // ensure that we populate this before everything starts
  inline  bool ensureRegistration() {
    const static auto reg = []() {
      return delphi_edm4hep::meta::DatamodelRegistryIndex::value() != podio::DatamodelRegistry::NoDefinitionAvailable;
    }();
    return reg;
  }

  const auto registrationEnsured = ensureRegistration();
}

} // namespace delphi_edm4hep::meta
