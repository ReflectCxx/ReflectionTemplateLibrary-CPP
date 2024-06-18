#pragma once

#include <memory>
#include <optional>
#include <unordered_map>
#include "Function.h"

namespace rtl {

	class NameSpace;

	class Record
	{
		using FunctionMap = std::unordered_map<std::string, Function>;

		std::string m_recordName;
		std::shared_ptr<FunctionMap> m_functions;
		std::shared_ptr<FunctionMap> m_constructors;

		Record(const std::string& pRecordName);

		void addFunction(const Function& pFunction) const;

		void addConstructor(const Function& pFunction) const;

		static void addFunction(const Function& pFunctions, std::unordered_map<std::string, Record>& pNamespaces);

	public: friend NameSpace;

		Record() = delete;
		Record(const Record& pRecord);
		Record(Record&& pRecord) noexcept;

		void operator=(const Record& pRecord);
		void operator=(Record&& pRecord) noexcept;

		std::optional<Function> getFunction(const std::string& pFunction) const;

		template<class ..._ctorArgs>
		std::unique_ptr<RObject> newInstance(_ctorArgs ...params) const;
	};
}