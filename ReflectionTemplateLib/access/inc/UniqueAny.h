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
			TypeQ m_qualifier;
			
			std::size_t m_typeId;
			std::any m_anyObject;

			std::function< void(const std::any&) > m_destructor;
			std::function< void(std::any&, std::size_t&) > m_toConst;

			UniqueAny();
			UniqueAny(const std::any& pAnyObj, const std::size_t pTypeId, const TypeQ pQualifier,
				  const std::function< void(const std::any&) >& pDctor,
				  const std::function< void(std::any&, std::size_t&) >& pToConst);

		public:

			UniqueAny(const UniqueAny&) = delete;
			operator std::any() const = delete;
			UniqueAny& operator=(const UniqueAny&) = delete;

			~UniqueAny();
			UniqueAny(UniqueAny&& pOther) noexcept;
			UniqueAny& operator=(UniqueAny&& pOther) noexcept;

			const bool isConst();

			const bool makeConst();

			template<class _type>
			constexpr const bool isOfType() const {
				return (detail::TypeId<_type>::get() == m_typeId);
			}

			GETTER(std::any, , m_anyObject);
			GETTER(TypeQ, Qualifier, m_qualifier);

			friend RStatus;
		};
	}
}