#pragma once

#include "Reflect.h"
#include "RecordBuilder.hpp"
#include "FunctionBuilder.hpp"

namespace rtl {

	namespace builder 
	{
		template<>
		inline const FunctionBuilder<> Reflect::function(const std::string& pFunction)
		{
			return FunctionBuilder<>(m_namespace, m_record, pFunction);
		}

		template<class _recordType>
		inline constexpr const RecordBuilder<_recordType> Reflect::record(const std::string& pClass)
		{
			return RecordBuilder<_recordType>(m_namespace, pClass);
		}

		template<class ..._signature>
		inline constexpr const FunctionBuilder<_signature...> Reflect::function(const std::string& pFunction) {
			return FunctionBuilder<_signature...>(m_namespace, m_record, pFunction);
		}
	}
}