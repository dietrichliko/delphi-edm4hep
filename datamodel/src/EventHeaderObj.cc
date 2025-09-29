// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#include "delphi_edm4hep/EventHeaderObj.h"
#include "podio/ObjectID.h"

namespace delphi {

EventHeaderObj::EventHeaderObj() :
  id(),
  data()
{  }

EventHeaderObj::EventHeaderObj(const podio::ObjectID id_, EventHeaderData data_) :
  id(id_), data(data_)
{  }

EventHeaderObj::EventHeaderObj(const EventHeaderObj& other) :
  id(),
  data(other.data)
{
}


} // namespace delphi

