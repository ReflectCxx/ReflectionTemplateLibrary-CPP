#pragma once

#include <optional>
#include <unordered_map>

namespace rtl {

	class Record;
	class Function;
	
	class NameSpace
	{
		//std::unordered_map<std::string, Record> m_records;
		std::unordered_map<std::string, Function> m_functions;

		NameSpace();

		void addFunction(const Function& pFunction);

	public:

		static void init(const std::vector<Function>& pFunctions, 
						 std::unordered_map<std::string, NameSpace>& pNamespaces);

		//std::optional<Record> getRecord(const std::string& pRecord);

		std::optional<Function> getFunction(const std::string& pFunction);
	};
}