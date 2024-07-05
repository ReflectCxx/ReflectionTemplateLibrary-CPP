#pragma once

#include <string>
#include "Constants.h"
#include "Builder.h"

namespace rtl {

	namespace builder 
	{
		template<class _recordType>
		class RecordBuilder;

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

			template<class ..._signature>
			constexpr const Builder<Member::NA, _signature...> function(const std::string& pFunction);

			template<class _recordType>
			constexpr const RecordBuilder<_recordType> record(const std::string& pClass);
		};
	}
}