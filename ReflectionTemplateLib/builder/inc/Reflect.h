#pragma once

#include <string>
#include "Constants.h"

namespace rtl {

	namespace builder 
	{
		template<class _recordType>
		class RecordBuilder;

		template<class ..._signature>
		class FunctionBuilder;

		// Builder class to encapsulate all type names, pointers.
		class Reflect
		{
			std::string m_record;
			std::string m_namespace;

		public:

			Reflect();
			Reflect(const Reflect&) = delete;
			Reflect& operator=(const Reflect&) = delete;

			Reflect& nameSpace(const std::string& pNamespace);

			template<class _recordType>
			inline constexpr const RecordBuilder<_recordType> record(const std::string& pClass);

			template<class ..._signature>
			inline constexpr const FunctionBuilder<_signature...> function(const std::string& pFunction);
		};
	}
}