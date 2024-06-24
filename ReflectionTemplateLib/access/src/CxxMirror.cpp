
#include "Record.h"
#include "Function.h"
#include "CxxMirror.h"
#include "Constants.h"
#include "FunctorContainer.hpp"

namespace rtl {
	
	namespace access 
	{
		CxxMirror::CxxMirror(std::vector<Function> pFunctions)
		{
			init(pFunctions);

			for (const auto& itr : m_namespaces) {
				const NameSpace& nameSpace = itr.second;
				nameSpace.init();
			}
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


		void CxxMirror::init(const std::vector<Function>& pFunctions)
		{
			for (const auto& function : pFunctions)
			{
				const auto& nameSpace = function.getNamespace();
				const auto& recordName = function.getRecordName();

				const auto& itr0 = m_namespaces.find(nameSpace);
				if (itr0 == m_namespaces.end()) {
					const auto& itr1 = m_namespaces.emplace(nameSpace, NameSpace());
					if (recordName.empty()) {
						itr1.first->second.addFunction(function);
					}
					else {
						itr1.first->second.addRecord(function);
					}
				}
				else {
					if (recordName.empty()) {
						itr0->second.addFunction(function);
					}
					else {
						itr0->second.addRecord(function);
					}
				}
			}
		}
	}
}