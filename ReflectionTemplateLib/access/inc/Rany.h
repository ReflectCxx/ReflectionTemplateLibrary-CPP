#pragma once

#include <any>
#include "TypeId.h"
#include "Constants.h"

namespace rtl {

	namespace access 
	{
		class Rany
		{
			std::any m_anyObject;
			const std::size_t m_typeId;

		public:

			Rany();
			Rany(const std::any pAnyObj, const std::size_t pTypeId);

			operator std::any() const = delete;

			GETTER(std::any, , m_anyObject);

			template<class _type>
			constexpr const bool isOfType() const {
				return (detail::TypeId<_type>::get() == m_typeId);
			}
		};
	}
}