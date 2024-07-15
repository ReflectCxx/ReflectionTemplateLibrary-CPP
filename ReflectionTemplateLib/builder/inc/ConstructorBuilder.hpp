#pragma once

#include "Function.h"
#include "Builder.hpp"
#include "ConstructorBuilder.h"

namespace rtl {

	namespace builder 
	{
		template<class _recordType, class ..._ctorSignature>
		inline ConstructorBuilder<_recordType, _ctorSignature...>::ConstructorBuilder(const std::string& pNamespace, const std::string& pRecord,
											      const FunctorType& pCtorType)
			: m_record(pRecord)
			, m_namespace(pNamespace)
			, m_ctorType(pCtorType)
		{
		}


		template<class _recordType, class ..._ctorSignature>
		inline constexpr const access::Function ConstructorBuilder<_recordType, _ctorSignature...>::build() const
		{
			switch (m_ctorType)
			{
			default:
			case FunctorType::Ctor: {
				const auto& ctorName = (m_record + Ctor::CTOR);
				return Builder<TypeQ::Mute>(m_namespace, m_record, ctorName).build<_recordType, _ctorSignature...>();
			}
			case FunctorType::CopyCtor: {
				const auto& ctorName = (m_record + Ctor::CTOR_COPY);
				return Builder<TypeQ::Mute>(m_namespace, m_record, ctorName).build<_recordType, _ctorSignature...>();
			}
			case FunctorType::CopyCtorConst: {
				const auto& ctorName = (m_record + Ctor::CTOR_CONST_COPY);
				return Builder<TypeQ::Mute>(m_namespace, m_record, ctorName).build<_recordType, _ctorSignature...>();
			}
			}
		}
	}


	namespace builder
	{
		template<class _recordType, class ..._signature>
		inline constexpr const ConstructorBuilder<_recordType, _signature...>
			ConstructorBuilder<>::select(const std::string& pNamespace, const std::string& pRecord,
				enable_if_same<_recordType&, typename detail::TypeId<_signature...>::HEAD > *_)
		{
			return ConstructorBuilder<_recordType, _signature...>(pNamespace, pRecord, FunctorType::CopyCtor);
		}


		template<class _recordType, class ..._signature>
		inline constexpr const ConstructorBuilder<_recordType, _signature...>
			ConstructorBuilder<>::select(const std::string& pNamespace, const std::string& pRecord,
				enable_if_same<const _recordType&, typename detail::TypeId<_signature...>::HEAD > *_)
		{
			return ConstructorBuilder<_recordType, _signature...>(pNamespace, pRecord, FunctorType::CopyCtorConst);
		}


		template<class _recordType, class ..._signature>
		inline constexpr const ConstructorBuilder<_recordType, _signature...>
			ConstructorBuilder<>::select(const std::string& pNamespace, const std::string& pRecord,
				enable_if_not_same<_recordType&, typename detail::TypeId<_signature...>::HEAD > *_,
				enable_if_not_same<const _recordType&, typename detail::TypeId<_signature...>::HEAD > *__)
		{
			return ConstructorBuilder<_recordType, _signature...>(pNamespace, pRecord, FunctorType::Ctor);
		}
	}
}