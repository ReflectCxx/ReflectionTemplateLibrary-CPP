#pragma once

#include <memory>
#include <optional>
#include <unordered_map>

namespace rtl {

	class Method;
	class RObject;
	class Function;
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

		std::optional<Method> getMethod(const std::string& pMethod) const;

		template<class ..._ctorArgs>
		std::unique_ptr<RObject> newInstance(_ctorArgs ...params) const;
	};
}