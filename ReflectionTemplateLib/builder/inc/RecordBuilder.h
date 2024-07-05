#pragma once

#include "Function.h"

namespace rtl {

	namespace builder 
	{
		template<class _recordType, class ..._ctorSignature>
		class ConstructorBuilder;

		template<class _recordType>
		class RecordBuilder 
		{
			const std::string& m_record;
			const std::string& m_namespace;

		public:

			RecordBuilder(const std::string& pNamespace, const std::string& pRecord);

			template<class ..._signature>
			constexpr const ConstructorBuilder<_recordType, _signature...> constructor() const;

			constexpr const Builder<Member::Mute> method(const std::string& pFunction) const;

			constexpr const Builder<Member::Const> methodConst(const std::string& pFunction) const;

			template<class ..._signature>
			constexpr const Builder<Member::Mute, _signature...> method(const std::string& pFunction) const;

			template<class ..._signature>
			constexpr const Builder<Member::Const, _signature...> methodConst(const std::string& pFunction) const;
		};
	}
}