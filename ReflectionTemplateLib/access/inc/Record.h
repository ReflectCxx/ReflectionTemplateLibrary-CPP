#pragma once

#include <memory>
#include <optional>
#include <unordered_map>

namespace rtl {

	namespace access 
	{
		class Rany;
		class Method;
		class Function;
		class NameSpace;

		class Record
		{
			friend NameSpace;

			using FunctionMap = std::unordered_map<std::string, Function>;

			std::string m_recordName;
			std::shared_ptr<FunctionMap> m_functions;

			Record(const std::string& pRecordName);

			void init() const;

			void addFunction(const Function& pFunction) const;

			static void addFunction(const Function& pFunction, std::unordered_map<std::string, Record>& pNamespaces);

		public:

			Record() = delete;
			Record(const Record& pRecord);
			Record(Record&& pRecord) noexcept;

			void operator=(const Record& pRecord);
			void operator=(Record&& pRecord) noexcept;

			std::optional<Method> getMethod(const std::string& pMethod) const;

			template<class ..._ctorArgs>
			Rany newInstance(_ctorArgs ...params) const;
		};
	}
}