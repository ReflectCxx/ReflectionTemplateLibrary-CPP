
#include <any>
#include "UniqueAny.h"

namespace rtl {

	namespace access 
	{
		UniqueAny::~UniqueAny()
		{
			if (m_destructor) {
				m_destructor(m_anyObject);
			}
		}

		
		UniqueAny::UniqueAny()
			: m_typeId(int(Type::NONE))
			, m_destructor(std::function<void(const std::any&)>()){
		}


		UniqueAny::UniqueAny(UniqueAny&& pOther) noexcept
			: m_typeId(pOther.m_typeId) 
		{
			m_anyObject = pOther.m_anyObject;
			m_destructor = std::move(pOther.m_destructor);
		}

		
		UniqueAny& UniqueAny::operator=(UniqueAny&& pOther) noexcept
		{
			m_typeId = pOther.m_typeId;
			m_anyObject = pOther.m_anyObject;
			m_destructor = std::move(pOther.m_destructor);
			return *this;
		}


		UniqueAny::UniqueAny(const std::any& pAnyObj, const std::size_t pTypeId, const std::function<void(const std::any&)>& pDctor)
			: m_anyObject(pAnyObj)
			, m_typeId(pTypeId)
			, m_destructor(pDctor) {
		}
	}
}