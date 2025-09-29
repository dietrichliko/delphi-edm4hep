// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#include "delphi_edm4hep/RunHeaderObj.h"
#include "podio/ObjectID.h"

namespace delphi {

RunHeaderObj::RunHeaderObj() :
  id(),
  data()
{  }

RunHeaderObj::RunHeaderObj(const podio::ObjectID id_, RunHeaderData data_) :
  id(id_), data(data_)
{  }

RunHeaderObj::RunHeaderObj(const RunHeaderObj& other) :
  id(),
  data(other.data)
{
}


} // namespace delphi

