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
				const auto& ctorName = CtorName::ctor(m_record);
				return Builder<TypeQ::Mute>(m_namespace, m_record, ctorName).build<_recordType, _ctorSignature...>();
			}
			case FunctorType::CopyCtor: {
				const auto& ctorName = CtorName::copy(m_record);
				return Builder<TypeQ::Mute>(m_namespace, m_record, ctorName).build<_recordType, _ctorSignature...>();
			}
			case FunctorType::CopyCtorConst: {
				const auto& ctorName = CtorName::constCopy(m_record);
				return Builder<TypeQ::Mute>(m_namespace, m_record, ctorName).build<_recordType, _ctorSignature...>();
			}
			}
		}
	}
}