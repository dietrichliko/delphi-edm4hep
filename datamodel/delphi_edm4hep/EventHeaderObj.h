// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#ifndef DELPHI_EDM4HEP_EventHeaderOBJ_H
#define DELPHI_EDM4HEP_EventHeaderOBJ_H

// data model specific includes
#include "delphi_edm4hep/EventHeaderData.h"

#include "podio/ObjectID.h"



namespace delphi {

class EventHeader;

class EventHeaderObj {
public:
  /// constructor
  EventHeaderObj();
  /// copy constructor (does a deep-copy of relation containers)
  EventHeaderObj(const EventHeaderObj&);
  /// constructor from ObjectID and EventHeaderData
  /// does not initialize the internal relation containers
  EventHeaderObj(const podio::ObjectID id, EventHeaderData data);
  /// No assignment operator
  EventHeaderObj& operator=(const EventHeaderObj&) = delete;
  virtual ~EventHeaderObj() = default;

public:
  podio::ObjectID id;
  EventHeaderData data;
};

} // namespace delphi


#endif
