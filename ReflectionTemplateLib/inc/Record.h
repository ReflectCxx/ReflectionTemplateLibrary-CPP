#pragma once

#include <memory>
#include <optional>
#include <unordered_map>
#include "Function.h"

namespace rtl {

	class Record
	{
		using FunctionMap = std::unordered_map<std::string, Function>;

		std::shared_ptr<FunctionMap> m_functions;

		Record();

		void addFunction(const Function& pFunction);

	public:

		
		Record(const Record& pRecord);
		Record(Record&& pRecord) noexcept;

		void operator=(const Record& pRecord);
		void operator=(Record&& pRecord) noexcept;

		std::optional<Function> getFunction(const std::string& pFunction);

		static void addFunction(const Function& pFunctions, std::unordered_map<std::string, Record>& pNamespaces);
	};
}