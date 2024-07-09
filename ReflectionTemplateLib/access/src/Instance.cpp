
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
		Instance::Instance()
			: m_qualifier(TypeQ::None)
			, m_typeId(detail::TypeId<>::None) {
		}


		Instance::Instance(const Instance& pOther)
			: m_qualifier(pOther.m_qualifier)
			, m_typeId(pOther.m_typeId)
			, m_anyObject(pOther.m_anyObject)
			, m_toConst(pOther.m_toConst)
			, m_destructor(pOther.m_destructor) {
		}


		Instance::Instance(const std::any& pAnyObj, const std::size_t pTypeId, const TypeQ pQualifier,
			const Function& pDctor, const Function& pConstConverter)
			: m_qualifier(pQualifier)
			, m_typeId(pTypeId)
			, m_anyObject(pAnyObj)
			, m_toConst(pConstConverter)
			, m_destructor(&g_instanceCount, [=](void* ptr) 
			{
				pDctor(pAnyObj, pQualifier);
				(*static_cast<std::size_t*>(ptr))--;
			})
		{
			g_instanceCount++;
		}


		const bool Instance::isEmpty() const {
			return (!m_anyObject.has_value());
		}


		const bool Instance::isConst() const {
			return (m_qualifier == TypeQ::Const);
		}


		const bool Instance::makeConst() const
		{
			const RStatus& ret = m_toConst(m_anyObject);
			if (ret.didCallSucceed()) {
				m_qualifier = TypeQ::Const;
				m_typeId = ret.getTypeId();
				m_anyObject = ret.get();
				return true;
			}
			return false;
		}
	}
}