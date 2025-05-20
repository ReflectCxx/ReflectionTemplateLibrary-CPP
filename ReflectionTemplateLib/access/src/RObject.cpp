
#include "RObject.h"
#include "TypeId.h"

namespace rtl::access {

	RObject::RObject(std::any pObjRef, std::size_t pTypeId, std::string pTypeStr, alloc pAllocOn,
                     const std::vector<Converter>& pConversions)
		: m_object(std::move(pObjRef))
		, m_typeId(pTypeId)
		, m_typeStr(pTypeStr + " ")
		, m_allocatedOn(pAllocOn)
		, m_converters(pConversions)
	{
		pObjRef.reset();
	}


	const std::size_t RObject::getConverterIndex(const std::size_t& pToTypeId)
	{
		for (std::size_t index = 0; index < m_converters.size(); index++)
		{
			if (m_converters[index].first == pToTypeId) {
				return index;
			}
		}
		return -1;
	}
}