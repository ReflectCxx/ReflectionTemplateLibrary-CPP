#pragma once

#include <any>
#include <memory>

#include "TypeId.h"
#include "Constants.h"
#include "Function.h"

namespace rtl {

	namespace access
	{
		class Record;

		class Instance
		{
			mutable TypeQ m_qualifier;
			mutable std::size_t m_typeId;
			mutable std::any m_anyObject;

			const Function m_toConst;
			const std::shared_ptr<void> m_destructor;

			explicit Instance();
			explicit Instance(const std::any& pAnyObj, const std::size_t pTypeId, const TypeQ pQualifier,
						   const Function& pDctor, const Function& pConstConverter);
		public:

			Instance(const Instance&);

			GETTER(std::any, , m_anyObject);
			GETTER(std::size_t, TypeId, m_typeId);
			GETTER(TypeQ, Qualifier, m_qualifier);

			const bool isEmpty() const;

			const bool isConst() const;

			const bool makeConst() const;

			template<class _type>
			constexpr const bool isOfType() const {
				return (detail::TypeId<_type>::get() == m_typeId);
			}

			friend Record;
		};
	}
}