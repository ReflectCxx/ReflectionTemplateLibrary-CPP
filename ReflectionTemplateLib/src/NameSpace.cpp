#include "NameSpace.h"
#include "Record.h"
#include "Function.h"

namespace rtl {

	NameSpace::NameSpace() {

	}

	void NameSpace::addFunction(const Function& pFunction)
	{
		m_functions.emplace(pFunction.getFunctionName(), pFunction);
	}


	//std::optional<Record> NameSpace::getRecord(const std::string& pRecord)
	//{
	//	const auto& itr = m_records.find(pRecord);
	//	if (itr != m_records.end()) {
	//		return std::optional(itr->second);
	//	}
	//	return std::nullopt;
	//}


	std::optional<Function> NameSpace::getFunction(const std::string& pFunction)
	{
		const auto& itr = m_functions.find(pFunction);
		if (itr != m_functions.end()) {
			return std::optional(itr->second);
		}
		return std::nullopt;
	}


	void NameSpace::init(const std::vector<Function>& pFunctions, std::unordered_map<std::string, NameSpace>& pNamespaces)
	{
		for (const auto& function : pFunctions) 
		{
			const auto& nameSpace = function.getNamespace();
			const auto& itr = pNamespaces.find(nameSpace);
			if (itr == pNamespaces.end()) {
				const auto& nsItr = pNamespaces.emplace(nameSpace, NameSpace());
				nsItr.first->second.addFunction(function);
			}
			else {
				itr->second.addFunction(function);
			}
		}
	}
}