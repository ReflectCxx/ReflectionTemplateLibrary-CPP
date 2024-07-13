
#include <any>

#include "TypeId.hpp"
#include "RStatus.h"
#include "Instance.h"
#include "Function.hpp"

namespace {

	static std::size_t g_instanceCount = 0;
}

namespace rtl {

	namespace access
	{
		const bool Instance::isEmpty() const {
			return (!m_anyObject.has_value());
		}


		const bool Instance::isConst() const {
			return (m_qualifier == TypeQ::Const);
		}


		std::size_t Instance::getInstanceCount() {
			return g_instanceCount;
		}


		void Instance::makeConst(const bool& pCastAway) {
			m_qualifier = (pCastAway ? TypeQ::Mute : TypeQ::Const);
		}


		Instance::Instance()
			: m_qualifier(TypeQ::None)
			, m_typeId(detail::TypeId<>::None)
			, m_constTypeId(detail::TypeId<>::None) {
		}


		Instance::Instance(const Instance& pOther)
			: m_qualifier(pOther.m_qualifier)
			, m_typeId(pOther.m_typeId)
			, m_constTypeId(pOther.m_constTypeId)
			, m_anyObject(pOther.m_anyObject)
			, m_destructor(pOther.m_destructor) {
		}


		Instance::Instance(const std::any& pRetObj, const RStatus& pStatus, const Function& pDctor)
			: m_qualifier(TypeQ::Mute)
			, m_typeId(pStatus.getTypeId())
			, m_constTypeId(pStatus.getTypeId())
			, m_anyObject(pRetObj)
			, m_destructor(&g_instanceCount, [=](void* ptr)
			{
				pDctor(pRetObj);
				(*static_cast<std::size_t*>(ptr))--;
			})
		{
			g_instanceCount++;
		}
	}
}