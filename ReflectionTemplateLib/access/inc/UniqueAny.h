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
			mutable TypeQ m_qualifier;
			mutable std::size_t m_typeId;
			mutable std::any m_anyObject;

			std::function< void(std::any&, std::size_t&) > m_toConst;
			std::function< void(const std::any&, const TypeQ&) > m_destructor;

			UniqueAny();
			UniqueAny(const std::any& pAnyObj, const std::size_t pTypeId, const TypeQ pQualifier,
				  const std::function< void(const std::any&, const TypeQ&) >& pDctor,
				  const std::function< void(std::any&, std::size_t&) >& pToConst);

		public:

			UniqueAny(const UniqueAny&) = delete;
			operator std::any() const = delete;
			UniqueAny& operator=(const UniqueAny&) = delete;

			~UniqueAny();
			UniqueAny(UniqueAny&& pOther) noexcept;
			UniqueAny& operator=(UniqueAny&& pOther) noexcept;

			const bool isConst() const;

			const bool makeConst() const;

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