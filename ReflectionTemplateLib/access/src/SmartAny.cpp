
#include <any>
#include "SmartAny.h"

namespace rtl {

	namespace access 
	{
		SmartAny::~SmartAny()
		{
			if (m_destructor) {
				m_destructor(m_anyObject);
			}
		}

		
		SmartAny::SmartAny()
			: m_typeId(int(Type::NONE))
			, m_destructor(std::function<void(const std::any&)>()){
		}


		SmartAny::SmartAny(SmartAny&& pOther) noexcept
			: m_typeId(pOther.m_typeId) 
		{
			m_anyObject = pOther.m_anyObject;
			m_destructor = pOther.m_destructor;
			pOther.m_destructor = std::function<void(const std::any&)>();
		}

		
		SmartAny& SmartAny::operator=(SmartAny&& pOther) noexcept
		{
			m_typeId = pOther.m_typeId;
			m_anyObject = pOther.m_anyObject;
			m_destructor = pOther.m_destructor;
			pOther.m_destructor = std::function<void(const std::any&)>();
			return *this;
		}


		SmartAny::SmartAny(const std::any& pAnyObj, const std::size_t pTypeId, const std::function<void(const std::any&)>& pDctor)
			: m_anyObject(pAnyObj)
			, m_typeId(pTypeId)
			, m_destructor(pDctor) {
		}
	}
}