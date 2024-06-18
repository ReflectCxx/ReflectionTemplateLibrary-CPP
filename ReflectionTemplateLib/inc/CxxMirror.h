#pragma once

#include <string>
#include <optional>
#include <unordered_map>

#include "RObject.hpp"
#include "NameSpace.h"

namespace rtl {

	class CxxMirror
	{
		std::unordered_map<std::string, NameSpace> m_namespaces;

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