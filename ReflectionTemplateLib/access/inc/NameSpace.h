#pragma once

#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>

namespace rtl {

	namespace access 
	{
		class Record;
		class Function;
		class NameSpace;
		class CxxMirror;

		class NameSpace
		{
			friend CxxMirror;

			using RecordsMap = std::unordered_map<std::string, Record>;
			using FunctionsMap = std::unordered_map<std::string, Function>;

			std::shared_ptr<RecordsMap> m_records;
			std::shared_ptr<FunctionsMap> m_functions;

			NameSpace();

			void addRecord(const Function& pFunction);

			void addFunction(const Function& pFunction);

			static void init(const std::vector<Function>& pFunctions, std::unordered_map<std::string, NameSpace>& pNamespaces);

		public:

			NameSpace(const NameSpace& pNameSpace);
			NameSpace(NameSpace&& pNameSpace) noexcept;

			void operator=(const NameSpace& pNameSpace);
			void operator=(NameSpace&& pNameSpace) noexcept;

			std::optional<Record> getRecord(const std::string& pRecord);

			std::optional<Function> getFunction(const std::string& pFunction);
		};
	}
}