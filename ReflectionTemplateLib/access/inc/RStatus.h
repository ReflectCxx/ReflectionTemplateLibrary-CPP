#pragma once

#include <any>
#include "Constants.h"
#include "TypeId.h"

namespace rtl
{
	namespace access
	{
		class RStatus
		{
			const bool m_callStatus;
			const std::any m_returnObj;
			const std::size_t m_typeId;
			const std::size_t m_typeIdConst;
			const TypeQ m_typeQualifier;

		public:

			RStatus(const bool pCallStatus);

			RStatus(const bool pCallStatus, const std::any& pRetObj, const std::size_t pTypeId,
				const std::size_t pConstTypeId, const TypeQ pQualifier);

			GETTER(std::any, Return, m_returnObj)
			GETTER(std::size_t, TypeId, m_typeId)
			GETTER(TypeQ, Qualifier, m_typeQualifier)

			operator bool() const {
				return m_callStatus;
			}

			template<class _type>
			constexpr const bool isOfType() const {
				return (m_typeQualifier == TypeQ::Mute && detail::TypeId<_type>::get() == m_typeId) ||
				       (m_typeQualifier == TypeQ::Const && detail::TypeId<_type>::get() == m_typeIdConst);
			}
		};
	}
}