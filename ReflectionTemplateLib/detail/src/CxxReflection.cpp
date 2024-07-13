
#include "TypeId.h"
#include "Record.h"
#include "Method.h"
#include "CxxReflection.h"

namespace rtl {

	namespace detail
	{
		CxxReflection::CxxReflection(const std::vector<access::Function>& pFunctions)
		{
			for (const auto& function : pFunctions) {
				organizeFunctorsMetaData(function);
			}
		}


		void CxxReflection::addRecord(RecordMap& pRecordMap, const access::Function& pFunction)
		{
			const auto& recordName = pFunction.getRecordName();
			const auto& itr = pRecordMap.find(recordName);
			if (itr == pRecordMap.end()) {
				const auto& recordItr = pRecordMap.emplace(recordName, access::Record(recordName));
				addMethod(recordItr.first->second.getFunctionsMap(),pFunction);
			}
			else {
				addMethod(itr->second.getFunctionsMap(), pFunction);
			}
		}


		void CxxReflection::addFunction(FunctionMap& pFunctionMap, const access::Function& pFunction)
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


		void CxxReflection::addMethod(MethodMap& pMethodMap, const access::Function& pFunction)
		{
			const auto& fname = pFunction.getFunctionName();
			const auto& itr = pMethodMap.find(fname);
			if (itr == pMethodMap.end())
			{
				if (pFunction.getFunctorType() == FunctorType::Ctor ||
					pFunction.getFunctorType() == FunctorType::CopyCtor ||
					pFunction.getFunctorType() == FunctorType::CopyCtorConst)
				{
					auto& functorIds = pFunction.getFunctorIds();
					if (functorIds.size() > 1) {

						const auto& dctorName = pFunction.getRecordName() + Ctor::DCTOR;
						if(pMethodMap.find(dctorName) == pMethodMap.end()){
							access::Method method = access::Method::getDestructorMethod(pFunction, functorIds[1]);
							pMethodMap.insert(std::make_pair(method.getFunctionName(), method));
						}
						functorIds.pop_back();
					}
				}
				pMethodMap.emplace(fname, access::Method(pFunction));
			}
			else {
				const auto& function = itr->second;
				function.addOverload(pFunction);
			}
		}


		void CxxReflection::organizeFunctorsMetaData(const access::Function& pFunction)
		{
			const auto& nameSpace = pFunction.getNamespace();

			if (pFunction.getRecordName().empty()) {
				const auto& itr = m_nsFunctionsMap.find(nameSpace);
				if (itr == m_nsFunctionsMap.end()) {
					const auto& funcMapItr = m_nsFunctionsMap.emplace(nameSpace, FunctionMap());
					addFunction(funcMapItr.first->second, pFunction);
				}
				else {
					addFunction(itr->second, pFunction);
				}
			}
			else {
				const auto& itr = m_nsRecordsMap.find(nameSpace);
				if (itr == m_nsRecordsMap.end()) {
					const auto& recordMapItr = m_nsRecordsMap.emplace(nameSpace, RecordMap());
					addRecord(recordMapItr.first->second, pFunction);
				}
				else {
					addRecord(itr->second, pFunction);
				}
			}
		}
	}
}