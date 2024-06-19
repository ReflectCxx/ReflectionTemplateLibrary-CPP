
#include "Record.h"
#include "Function.h"
#include "CxxMirror.h"
#include "Constants.h"
#include "NameSpace.h"
#include "FunctorContainer.hpp"

namespace rtl {
	
	CxxMirror::CxxMirror(std::vector<Function> pFunctions)
	{
		NameSpace::init(pFunctions, m_namespaces);
	}

	
	std::optional<Record> CxxMirror::getRecord(const std::string& pRecord)
	{
		return getRecord(NS_GLOBAL, pRecord);
	}


	std::optional<Function> CxxMirror::getFunction(const std::string& pFunction)
	{
		return getFunction(NS_GLOBAL, pFunction);
	}


	std::optional<Record> CxxMirror::getRecord(const std::string& pNameSpace, const std::string& pRecord)
	{
		const auto& itr = m_namespaces.find(pNameSpace);
		if (itr != m_namespaces.end()) {
			return itr->second.getRecord(pRecord);
		}
		return std::nullopt;
	}


	std::optional<Function> CxxMirror::getFunction(const std::string& pNameSpace, const std::string& pFunction)
	{
		const auto& itr = m_namespaces.find(pNameSpace);
		if (itr != m_namespaces.end()) {
			return itr->second.getFunction(pFunction);
		}
		return std::nullopt;
	}
}