#pragma once

#include <string>
#include <optional>
#include <unordered_map>

#include "CxxReflection.h"

namespace rtl {

	namespace access 
	{
		class Record;
		class Function;

		class CxxMirror : detail::CxxReflection 
		{
		public:

			CxxMirror(const std::vector<Function>& pFunctions);

			std::optional<Record> getRecord(const std::string& pFunction);

			std::optional<Function> getFunction(const std::string& pFunction);

			std::optional<Record> getRecord(const std::string& pNameSpace, const std::string& pFunction);

			std::optional<Function> getFunction(const std::string& pNameSpace, const std::string& pFunction);
		};
	}
}