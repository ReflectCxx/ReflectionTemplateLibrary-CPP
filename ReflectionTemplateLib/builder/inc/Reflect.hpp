#pragma once

#include "Reflect.h"
#include "Builder.hpp"
#include "RecordBuilder.hpp"

namespace rtl {

	namespace builder 
	{
		inline Reflect::Reflect()
			: m_record("")
			, m_namespace(NAMESPACE_GLOBAL) {
		}

		
		inline Reflect& Reflect::nameSpace(const std::string& pNamespace)
		{
			m_namespace = pNamespace;
			return *this;
		}


		template<>
		inline const Builder<Member::NA> Reflect::function(const std::string& pFunction)
		{
			return Builder<Member::NA>(m_namespace, m_record, pFunction);
		}

		
		template<class _recordType>
		inline constexpr const RecordBuilder<_recordType> Reflect::record(const std::string& pClass)
		{
			return RecordBuilder<_recordType>(m_namespace, pClass);
		}

		
		template<class ..._signature>
		inline constexpr const Builder<Member::NA, _signature...> Reflect::function(const std::string& pFunction) {
			return Builder<Member::NA, _signature...>(m_namespace, m_record, pFunction);
		}
	}
}