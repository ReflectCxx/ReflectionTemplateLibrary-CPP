#pragma once

#include "Function.h"
#include "FunctionBuilder.hpp"
#include "ConstructorBuilder.h"

namespace rtl {

	namespace builder 
	{
		template<class _recordType, class ..._ctorSignature>
		inline ConstructorBuilder<_recordType, _ctorSignature...>::ConstructorBuilder(const std::string& pNamespace, const std::string& pRecord)
			: m_record(pRecord)
			, m_namespace(pNamespace)
		{
		}


		template<class _recordType, class ..._ctorSignature>
		inline constexpr const access::Function ConstructorBuilder<_recordType, _ctorSignature...>::build() const
		{
			const auto& functionName = m_record + CTOR_SUFFIX;
			return FunctionBuilder<>(m_namespace, m_record, functionName).build<_recordType, _ctorSignature...>();
		}
	}
}