
#include "RObject.h"
#include "TypeId.h"

namespace rtl::access {

	RObject::RObject(std::any pObjRef, std::size_t pTypeId, std::string pTypeStr, alloc pAllocOn)
		: m_object(std::move(pObjRef))
		, m_typeId(pTypeId)
		, m_typeStr(pTypeStr)
		, m_allocatedOn(pAllocOn)
	{
		pObjRef.reset();
	}


	RObject::RObject(RObject&& pOther) noexcept
		: m_object(std::move(pOther.m_object))
		, m_typeId(pOther.m_typeId)
		, m_typeStr(pOther.m_typeStr)
		, m_allocatedOn(pOther.m_allocatedOn)
	{
		pOther.m_object.reset();
	}


	RObject& RObject::operator=(RObject&& pOther) noexcept
	{
		if (&pOther == this) {
			return *this;
		}

		m_object = std::move(pOther.m_object);
		m_typeId = pOther.m_typeId;
		m_typeStr = pOther.m_typeStr;
		m_allocatedOn = pOther.m_allocatedOn;
		pOther.m_object.reset();
		return *this;
	}
}

