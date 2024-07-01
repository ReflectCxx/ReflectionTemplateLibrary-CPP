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

			inline constexpr const FunctionBuilder<> method(const std::string& pFunction) const;

			template<class ..._signature>
			inline constexpr const FunctionBuilder<_signature...> method(const std::string& pFunction) const;

			template<class ..._signature>
			inline constexpr const ConstructorBuilder<_recordType, _signature...> constructor() const;
		};
	}
}