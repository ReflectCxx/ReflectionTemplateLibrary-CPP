

#include "ReflectTypeMeta.h"


namespace rtl {

	namespace detail 
	{
		ReflectTypeMeta::ReflectTypeMeta(const std::vector<access::Function>& pFunctions)
		{
			for (const auto& function : pFunctions) {
				initTypeMetaData(function);
			}

			for (const auto& itr : m_nsFunctionsMap)
			{
				for (const auto& itr0 : itr.second) {
					itr0.second.sortFunctorsHash();
				}
			}

			for (const auto& itr : m_nsRecordsMap)
			{
				for (const auto& itr1 : itr.second) {
					for (const auto& itr0 : itr1.second) {
						itr0.second.sortFunctorsHash();
					}
				}
			}
		}


		void ReflectTypeMeta::addFunction(RecordMap& pRecordMap, const access::Function& pFunction)
		{
			const auto& recordName = pFunction.getRecordName();
			const auto& itr = pRecordMap.find(recordName);
			if (itr == pRecordMap.end()) {
				const auto& itr0 = pRecordMap.emplace(recordName, FunctionMap());
				addFunction(itr0.first->second, pFunction);
			}
			else {
				addFunction(itr->second, pFunction);
			}
		}


		void ReflectTypeMeta::addFunction(FunctionMap& pFunctionMap, const access::Function& pFunction)
		{
			const auto& fname = pFunction.getFunctionName();
			const auto& itr = pFunctionMap.find(fname);
			if (itr == pFunctionMap.end()) {
				pFunctionMap.emplace(fname, pFunction);
			}
			else {
				const auto& function = itr->second;
				function.addOverload(pFunction);
			}
		}


		void ReflectTypeMeta::initTypeMetaData(const access::Function& pFunction)
		{
			const auto& nameSpace = pFunction.getNamespace();

			if (pFunction.getRecordName().empty()) {
				const auto& itr = m_nsFunctionsMap.find(nameSpace);
				if (itr == m_nsFunctionsMap.end()) {
					const auto& itr0 = m_nsFunctionsMap.emplace(nameSpace, FunctionMap());
					addFunction(itr0.first->second, pFunction);
				}
				else {
					addFunction(itr->second, pFunction);
				}
			}
			else {
				const auto& itr = m_nsRecordsMap.find(nameSpace);
				if (itr == m_nsRecordsMap.end()) {
					const auto& itr0 = m_nsRecordsMap.emplace(nameSpace, RecordMap());
					addFunction(itr0.first->second, pFunction);
				}
				else {
					addFunction(itr->second, pFunction);
				}
			}
		}
	}
}