#pragma once

#include <any>
#include <functional>

#include "TypeId.h"
#include "Constants.h"

namespace rtl {

	namespace detail
	{
		template<class ..._signature>
		class FunctorContainer;
	}

	namespace access
	{
		class Record;
		class Function;

		class SmartAny
		{
			friend class Record;
			friend class Function;

			template<class ..._signature>
			friend class detail::FunctorContainer;

			std::any m_anyObject;
			const std::size_t m_typeId;

			std::function<void(const std::any&)> m_destructor;

			SmartAny();
			SmartAny(const std::any pAnyObj, const std::size_t pTypeId,
				 const std::function<void(const std::any&)>& pDctor = std::function<void(const std::any&)>());

		public:

			SmartAny(SmartAny&) = delete;
			SmartAny(const SmartAny&) = delete;
			
			operator std::any() const = delete;
			void operator=(const SmartAny&) = delete;

			~SmartAny();
			SmartAny(SmartAny&& pOther) noexcept;
			void operator=(SmartAny&& pOther) noexcept;

			GETTER(std::any, , m_anyObject);

			template<class _type>
			constexpr const bool isOfType() const {
				return (detail::TypeId<_type>::get() == m_typeId);
			}
		};
	}
}