// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#ifndef DELPHI_EDM4HEP_RunHeaderOBJ_H
#define DELPHI_EDM4HEP_RunHeaderOBJ_H

// data model specific includes
#include "delphi_edm4hep/RunHeaderData.h"

#include "podio/ObjectID.h"



namespace delphi {

class RunHeader;

class RunHeaderObj {
public:
  /// constructor
  RunHeaderObj();
  /// copy constructor (does a deep-copy of relation containers)
  RunHeaderObj(const RunHeaderObj&);
  /// constructor from ObjectID and RunHeaderData
  /// does not initialize the internal relation containers
  RunHeaderObj(const podio::ObjectID id, RunHeaderData data);
  /// No assignment operator
  RunHeaderObj& operator=(const RunHeaderObj&) = delete;
  virtual ~RunHeaderObj() = default;

public:
  podio::ObjectID id;
  RunHeaderData data;
};

} // namespace delphi


#endif
