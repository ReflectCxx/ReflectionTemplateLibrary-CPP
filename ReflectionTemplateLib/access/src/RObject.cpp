
#include "RObject.h"
#include "TypeId.h"

namespace rtl::access {

	RObject::RObject(std::any pObjRef, std::size_t pTypeId, std::string pTypeStr, alloc pAllocOn,
                     const std::vector<std::pair<std::size_t, rtl::detail::Converter>>& pConversions)
		: m_object(std::move(pObjRef))
		, m_typeId(pTypeId)
		, m_typeStr(pTypeStr + " ")
		, m_allocatedOn(pAllocOn)
		, m_converters(pConversions)
	{
		pObjRef.reset();
	}


	const std::size_t RObject::getConverterIndex(const std::size_t& pToTypeId) const
	{
		for (std::size_t index = 0; index < m_converters.size(); index++) 
		{
			if (m_converters[index].first == pToTypeId) {
				return index;
			}
		}
		return -1;
	}


	RObject::RObject(RObject&& pOther) noexcept
		: m_object(std::move(pOther.m_object))
		, m_typeId(pOther.m_typeId)
		, m_typeStr(pOther.m_typeStr)
		, m_allocatedOn(pOther.m_allocatedOn)
		, m_converters(pOther.m_converters)
	{
		pOther.m_object.reset();
		pOther.m_typeId = rtl::detail::TypeId<>::None;
		pOther.m_typeStr = rtl::detail::TypeId<>::toString();
		pOther.m_allocatedOn = alloc::None;
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

		//TODO:
		//enable move ops for const&-vector m_converters

		return *this;
	}
}