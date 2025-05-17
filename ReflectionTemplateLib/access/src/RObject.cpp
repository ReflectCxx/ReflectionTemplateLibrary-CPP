
#include "RObject.h"
#include "TypeId.h"

namespace rtl::access {

	RObject::RObject(std::any&& pObjRef, std::size_t&& pTypeId, std::string&& pTypeStr)
		: m_object(std::move(pObjRef))
		, m_typeId(pTypeId)
		, m_typeStr(pTypeStr)
	{

	}
}

