#pragma once

#include <any>
#include <functional>

#include "TypeId.h"
#include "Constants.h"

namespace rtl {

	namespace access
	{
		class RStatus;

		class UniqueAny
		{
			std::any m_anyObject;
			std::size_t m_typeId;
			std::function<void(const std::any&)> m_destructor;

			UniqueAny();
			UniqueAny(const std::any& pAnyObj, const std::size_t pTypeId,
				  const std::function<void(const std::any&)>& pDctor = std::function<void(const std::any&)>());

		public:

			UniqueAny(const UniqueAny&) = delete;
			operator std::any() const = delete;
			UniqueAny& operator=(const UniqueAny&) = delete;

			~UniqueAny();
			UniqueAny(UniqueAny&& pOther) noexcept;
			UniqueAny& operator=(UniqueAny&& pOther) noexcept;

			GETTER(std::any, , m_anyObject);

			template<class _type>
			constexpr const bool isOfType() const {
				return (detail::TypeId<_type>::get() == m_typeId);
			}

			friend RStatus;
		};
	}
}