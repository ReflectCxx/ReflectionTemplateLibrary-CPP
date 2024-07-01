#pragma once

#include <any>
#include <functional>

#include "TypeId.h"
#include "Constants.h"

namespace rtl {

	namespace access
	{
		class RStatus;

		class SmartAny
		{
			std::any m_anyObject;
			std::size_t m_typeId;
			std::function<void(const std::any&)> m_destructor;

			SmartAny();
			SmartAny(const std::any& pAnyObj, const std::size_t pTypeId,
				 const std::function<void(const std::any&)>& pDctor = std::function<void(const std::any&)>());

		public:

			SmartAny(const SmartAny&) = delete;
			operator std::any() const = delete;
			SmartAny& operator=(const SmartAny&) = delete;

			~SmartAny();
			SmartAny(SmartAny&& pOther) noexcept;
			SmartAny& operator=(SmartAny&& pOther) noexcept;

			GETTER(std::any, Return, m_anyObject);

			template<class _type>
			constexpr const bool isOfType() const {
				return (detail::TypeId<_type>::get() == m_typeId);
			}

			friend RStatus;
		};
	}
}