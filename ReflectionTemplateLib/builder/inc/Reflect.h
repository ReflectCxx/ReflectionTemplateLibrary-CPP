#pragma once

#include "Constants.h"
#include "NameSpace.h"
#include "RecordBuilder.hpp"
#include "FunctionBuilder.hpp"
#include "ConstructorBuilder.hpp"

namespace rtl {

	namespace builder 
	{
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