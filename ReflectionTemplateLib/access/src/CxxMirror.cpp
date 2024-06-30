
#include "Record.h"
#include "Function.h"
#include "CxxMirror.h"
#include "Constants.h"
#include "FunctorContainer.hpp"

namespace rtl {
	
	namespace access 
	{
		CxxMirror::CxxMirror(std::vector<Function> pFunctions)
			:m_reflectTypeMeta(pFunctions)
		{
		}


		std::optional<Record> CxxMirror::getRecord(const std::string& pRecord)
		{
			return getRecord(NAMESPACE_GLOBAL, pRecord);
		}


		std::optional<Function> CxxMirror::getFunction(const std::string& pFunction)
		{
			return getFunction(NAMESPACE_GLOBAL, pFunction);
		}


		std::optional<Record> CxxMirror::getRecord(const std::string& pNameSpace, const std::string& pRecord)
		{
			const auto& nsRecordMap = m_reflectTypeMeta.getNamespaceRecordMap();
			const auto& itr = nsRecordMap.find(pNameSpace);
			if (itr != nsRecordMap.end()) 
			{
				const auto& recordMap = itr->second;
				const auto& itr0 = recordMap.find(pRecord);
				if (itr0 != recordMap.end()) {
					return std::make_optional(itr0->second);
				}
			}
			return std::nullopt;
		}


		std::optional<Function> CxxMirror::getFunction(const std::string& pNameSpace, const std::string& pFunction)
		{
			const auto& nsFunctionMap = m_reflectTypeMeta.getNamespaceFunctionsMap();
			const auto& itr = nsFunctionMap.find(pNameSpace);
			if (itr != nsFunctionMap.end()) 
			{
				const auto& functionMap = itr->second;
				const auto& itr0 = functionMap.find(pFunction);
				if (itr0 != functionMap.end()) {
					return std::make_optional(itr0->second);
				}
			}
			return std::nullopt;
		}
	}
}