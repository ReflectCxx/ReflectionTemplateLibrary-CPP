#pragma once

#include "Function.h"
#include "MethodBuilder.hpp"
#include "ConstructorBuilder.hpp"

namespace rtl {

	namespace builder 
	{
		template<class _recordType>
		class RecordBuilder 
		{
			const std::string& m_record;
			const std::string& m_namespace;

		public:

			RecordBuilder(const std::string& pNamespace, const std::string& pRecord);

			template<class ..._signature>
			inline constexpr const ConstructorBuilder<_recordType, _signature...> constructor() const;

			template<class ..._signature>
			inline constexpr const MethodBuilder<_recordType, _signature...> method(const std::string& pMethod) const;
		};
	}
}