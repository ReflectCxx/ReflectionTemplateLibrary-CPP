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
			const TypeQ m_typeQualifier;

		public:

			RStatus(const bool pCallStatus);

			RStatus(const bool pCallStatus, const std::any& pRetObj,
				const std::size_t pTypeId, const TypeQ pQualifier);

			const bool didCallSucceed() const;

			GETTER(std::size_t, TypeId, m_typeId)
			GETTER(std::any, , m_returnObj)

			template<class _type>
			constexpr const bool isOfType() const {
				return (detail::TypeId<_type>::get() == m_typeId);
			}
		};
	}
}