#pragma once

#include "Constants.h"

namespace rtl {

	namespace builder 
	{
		template<class _recordType = void, class ..._ctorSignature>
		class ConstructorBuilder
		{
			const std::string& m_record;
			const std::string& m_namespace;
			const FunctorType m_ctorType;

			ConstructorBuilder() = delete;

		public:

			ConstructorBuilder(const std::string& pNamespace, const std::string& pRecord,
					   const FunctorType& pCtorType);

			inline constexpr const access::Function build() const;
		};
	}


	namespace builder
	{
		template<>
		class ConstructorBuilder<>
		{
		public:

			template<class _recordType, class ..._signature>
			static constexpr const ConstructorBuilder<_recordType, _signature...>
				select(const std::string& pNamespace, const std::string& pRecord,
					enable_if_same<_recordType&, typename detail::TypeId<_signature...>::HEAD > *_= nullptr);


			template<class _recordType, class ..._signature>
			static constexpr const ConstructorBuilder<_recordType, _signature...>
				select(const std::string& pNamespace, const std::string& pRecord,
					enable_if_same<const _recordType&, typename detail::TypeId<_signature...>::HEAD > *_= nullptr);


			template<class _recordType, class ..._signature>
			static constexpr const ConstructorBuilder<_recordType, _signature...>
				select(const std::string& pNamespace, const std::string& pRecord,
					enable_if_not_same<_recordType&, typename detail::TypeId<_signature...>::HEAD > *_= nullptr,
					enable_if_not_same<const _recordType&, typename detail::TypeId<_signature...>::HEAD > *__= nullptr);
		};
	}
}