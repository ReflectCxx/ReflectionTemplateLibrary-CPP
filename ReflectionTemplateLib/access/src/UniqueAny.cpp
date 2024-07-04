
#include <any>

#include "TypeId.h"
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
			: m_qualifier(TypeQ::Vol)
			, m_typeId(detail::TypeId<>::None) {
		}


		UniqueAny::UniqueAny(UniqueAny&& pOther) noexcept
			: m_qualifier(pOther.m_qualifier)
			, m_typeId(pOther.m_typeId)
			, m_anyObject(pOther.m_anyObject)
			, m_destructor(std::move(pOther.m_destructor))
			, m_toConst(std::move(pOther.m_toConst)) {
		}

		
		UniqueAny& UniqueAny::operator=(UniqueAny&& pOther) noexcept
		{
			m_typeId = pOther.m_typeId;
			m_anyObject = pOther.m_anyObject;
			m_toConst = std::move(pOther.m_toConst);
			m_destructor = std::move(pOther.m_destructor);
			return *this;
		}


		UniqueAny::UniqueAny(const std::any& pAnyObj, const std::size_t pTypeId, const TypeQ pQualifier,
				     const std::function< void(const std::any&) >& pDctor,
				     const std::function< void(std::any&, std::size_t&) >& pToConst)
			: m_qualifier(pQualifier)
			, m_typeId(pTypeId)
			, m_anyObject(pAnyObj)
			, m_destructor(pDctor)
			, m_toConst(pToConst) {
		}


		const bool UniqueAny::isConst() {
			return (m_qualifier == TypeQ::Const);
		}


		const bool UniqueAny::makeConst()
		{
			if (m_toConst) {
				m_qualifier = TypeQ::Const;
				m_toConst(m_anyObject, m_typeId);
				return true;
			}
			return false;
		}
	}
}