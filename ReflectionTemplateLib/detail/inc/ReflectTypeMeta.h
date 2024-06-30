#pragma once

#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

#include "Constants.h"

namespace rtl {

	namespace access 
	{
		class Record;
		class Function;
		class CxxMirror;
	}

	namespace detail 
	{
		using RecordMap = std::unordered_map <std::string, access::Record>;
		using FunctionMap = std::unordered_map <std::string, access::Function>;

		class ReflectTypeMeta
		{
			friend class access::CxxMirror;

			std::unordered_map<std::string, RecordMap> m_nsRecordsMap;
			std::unordered_map<std::string, FunctionMap> m_nsFunctionsMap;

			void initTypeMetaData(const access::Function& pFunction);

			void addFunction(RecordMap& pRecordMap, const access::Function& pFunction);

			void addFunction(FunctionMap& pFunctionMap, const access::Function& pFunction);

			ReflectTypeMeta(const std::vector<access::Function>& pFunctions);

		public:

			ReflectTypeMeta() = delete;
			ReflectTypeMeta(ReflectTypeMeta&) = delete;
			ReflectTypeMeta& operator=(ReflectTypeMeta&) = delete;

			constexpr const std::unordered_map<std::string, RecordMap>& getNamespaceRecordMap() {
				return m_nsRecordsMap;
			}

			constexpr const std::unordered_map<std::string, FunctionMap>& getNamespaceFunctionsMap() {
				return m_nsFunctionsMap;
			}
		};
	}
}