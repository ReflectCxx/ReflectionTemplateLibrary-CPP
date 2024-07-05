#pragma once

#include "RecordBuilder.h"
#include "ConstructorBuilder.hpp"

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
		inline constexpr const Builder<Member::Mute> RecordBuilder<_recordType>::method(const std::string& pFunction) const
		{
			return Builder<Member::Mute>(m_namespace, m_record, pFunction);
		}


		template<class _recordType>
		inline constexpr const Builder<Member::Const> RecordBuilder<_recordType>::methodConst(const std::string& pFunction) const
		{
			return Builder<Member::Const>(m_namespace, m_record, pFunction);
		}


		template<class _recordType>
		template<class ..._signature>
		inline constexpr const Builder<Member::Mute, _signature...> RecordBuilder<_recordType>::method(const std::string& pFunction) const 
		{
			return Builder<Member::Mute, _signature...>(m_namespace, m_record, pFunction);
		}


		template<class _recordType>
		template<class ..._signature>
		inline constexpr const Builder<Member::Const, _signature...> RecordBuilder<_recordType>::methodConst(const std::string& pFunction) const 
		{
			return Builder<Member::Const, _signature...>(m_namespace, m_record, pFunction);
		}
	}
}