#pragma once

#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>

#include "Function.h"
#include "Record.h"

namespace rtl {

	class NameSpace
	{
		using RecordsMap = std::unordered_map<std::string, Record>;
		using FunctionsMap = std::unordered_map<std::string, Function>;

		std::shared_ptr<RecordsMap> m_records;
		std::shared_ptr<FunctionsMap> m_functions;

		NameSpace();

		void addRecord(const Function& pFunction);

		void addFunction(const Function& pFunction);

	public:

		NameSpace(const NameSpace& pNameSpace);
		NameSpace(NameSpace&& pNameSpace) noexcept;

		void operator=(const NameSpace& pNameSpace);
		void operator=(NameSpace&& pNameSpace) noexcept;

		std::optional<Record> getRecord(const std::string& pRecord);

		std::optional<Function> getFunction(const std::string& pFunction);

		static void init(const std::vector<Function>& pFunctions, std::unordered_map<std::string, NameSpace>& pNamespaces);
	};
}