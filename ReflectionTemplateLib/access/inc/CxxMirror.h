#pragma once

#include <string>
#include <optional>
#include <unordered_map>

#include "ReflectTypeMeta.h"

namespace rtl {

	namespace detail {
		class ReflectTypeMeta;
	}

	namespace access 
	{
		class Record;
		class Function;

		class CxxMirror
		{
			detail::ReflectTypeMeta m_reflectTypeMeta;

		public:

			CxxMirror() = delete;
			CxxMirror(CxxMirror&) = delete;
			CxxMirror& operator=(CxxMirror&) = delete;
			CxxMirror(std::vector<Function> pFunctions);

			std::optional<Record> getRecord(const std::string& pFunction);

			std::optional<Record> getRecord(const std::string& pNameSpace, const std::string& pFunction);

			std::optional<Function> getFunction(const std::string& pFunction);

			std::optional<Function> getFunction(const std::string& pNameSpace, const std::string& pFunction);
		};
	}
}