#pragma once

#include "RecordBuilder.h"

namespace rtl {

	namespace builder
	{
		template<class _recordType>
		inline RecordBuilder<_recordType>::RecordBuilder(const std::string& pNamespace, const std::string& pRecord)
			: m_record(pRecord)
			, m_namespace(pNamespace) {

		}


		template<class _recordType>
		template<class ..._signature>
		inline constexpr const ConstructorBuilder<_recordType, _signature...> RecordBuilder<_recordType>::constructor() const
		{
			return ConstructorBuilder<_recordType, _signature...>(m_namespace, m_record);
		}


		template<class _recordType>
		template<class ..._signature>
		inline constexpr const MethodBuilder<_recordType, _signature...> RecordBuilder<_recordType>::method(const std::string& pMethod) const
		{
			return MethodBuilder<_recordType, _signature...>(m_namespace, m_record, pMethod);
		}
	}
}