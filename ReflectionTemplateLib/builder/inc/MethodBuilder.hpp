#pragma once

#include "Function.h"
#include "FunctionBuilder.hpp"
#include "MethodBuilder.h"

namespace rtl {

	namespace builder 
	{
		template<class _recordType, class ..._signature>
		inline MethodBuilder<_recordType, _signature...>::MethodBuilder(const std::string& pNamespace, const std::string& pRecord, const std::string& pMethod)
			: m_record(pRecord)
			, m_method(pMethod)
			, m_namespace(pNamespace)
		{
		}


		template<class _recordType, class ..._signature>
		template<class _returnType>
		inline constexpr const access::Function MethodBuilder<_recordType, _signature...>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
		{
			return FunctionBuilder<>(m_namespace, m_record, m_method).build<_recordType, _signature...>(pFunctor);
		}
	}
}