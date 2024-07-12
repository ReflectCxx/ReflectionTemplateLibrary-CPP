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
			const Error m_callStatus;
			const TypeQ m_typeQualifier;

			const std::any m_returnObj;
			const std::size_t m_typeId;

		public:

			RStatus(const Error pCallStatus);

			RStatus(const std::any& pRetObj, const std::size_t pTypeId, const TypeQ pQualifier);

			GETTER(std::any, Return, m_returnObj)
			GETTER(std::size_t, TypeId, m_typeId)
			GETTER(TypeQ, Qualifier, m_typeQualifier)

			operator bool() const {
				return (m_callStatus == Error::None);
			}

			const bool operator==(const Error pError) const {
				return (m_callStatus == pError);
			}

			template<class _type>
			constexpr const bool isOfType() const {
				return (detail::TypeId<_type>::get() == m_typeId);
			}
		};
	}
}