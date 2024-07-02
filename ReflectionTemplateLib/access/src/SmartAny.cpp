
#include <any>
#include "SmartAny.h"

namespace rtl {

	namespace access 
	{
		SmartAny::SmartAny()
			: m_typeId(0) {
		}

		SmartAny::SmartAny(SmartAny&& pOther) noexcept
			: m_typeId(pOther.m_typeId)
		{
			m_anyObject = pOther.m_anyObject;
			m_destructor = pOther.m_destructor;
			pOther.m_destructor = std::function<void(const std::any&)>();
		} 

		void SmartAny::operator=(SmartAny&& pOther) noexcept
		{
			m_anyObject = pOther.m_anyObject;
			m_destructor = pOther.m_destructor;
			pOther.m_destructor = std::function<void(const std::any&)>();
		}


		SmartAny::SmartAny(const std::any pAnyObj, const std::size_t pTypeId, const std::function<void(const std::any&)>& pDctor)
			: m_anyObject(pAnyObj)
			, m_typeId(pTypeId)
			, m_destructor(pDctor) {
		}

		SmartAny::~SmartAny()
		{
			if (m_destructor) {
				m_destructor(m_anyObject);
			}
		}
	}
}