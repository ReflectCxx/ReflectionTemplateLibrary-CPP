#pragma once

#include <string>
#include <optional>
#include <unordered_map>

#include "Constants.h"

namespace rtl {

	namespace access 
	{
		class Record;
		class Method;
		class Function;
	}

	namespace detail
	{
		class CxxReflection
		{
			using RecordMap = std::unordered_map <std::string, access::Record>;
			using MethodMap = std::unordered_map <std::string, access::Method>;
			using FunctionMap = std::unordered_map <std::string, access::Function>;

			std::unordered_map<std::string, RecordMap> m_nsRecordsMap;
			std::unordered_map<std::string, FunctionMap> m_nsFunctionsMap;

			void organizeFunctorsMetaData(const access::Function& pFunction);

			void addRecord(RecordMap& pRecordMap, const access::Function& pFunction);
			void addMethod(MethodMap& pMethodMap, const access::Function& pFunction);
			void addFunction(FunctionMap& pFunctionMap, const access::Function& pFunction);

		protected:

			CxxReflection() = delete;
			CxxReflection(CxxReflection&) = delete;
			CxxReflection& operator=(CxxReflection&) = delete;

			CxxReflection(const std::vector<access::Function>& pFunctions);

		public:

			constexpr const std::unordered_map<std::string, RecordMap>& getNamespaceRecordMap() {
				return m_nsRecordsMap;
			}

			constexpr const std::unordered_map<std::string, FunctionMap>& getNamespaceFunctionsMap() {
				return m_nsFunctionsMap;
			}
		};
	}
}