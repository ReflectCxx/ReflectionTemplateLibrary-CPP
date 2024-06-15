#include "NameSpace.h"

namespace rtl {

	NameSpace::NameSpace()
		: m_records(new RecordsMap())
		, m_functions(new FunctionsMap())
	{
	}


	NameSpace::NameSpace(const NameSpace& pNameSpace)
		: m_records(pNameSpace.m_records)
		, m_functions(pNameSpace.m_functions)
	{
	}


	NameSpace::NameSpace(NameSpace&& pNameSpace) noexcept
		: m_records(std::move(pNameSpace.m_records))
		, m_functions(std::move(pNameSpace.m_functions))
	{
	}


	void NameSpace::operator=(const NameSpace& pNameSpace)
	{
		if (this == &pNameSpace) {
			return;
		}
		m_records = pNameSpace.m_records;
		m_functions = pNameSpace.m_functions;
	}


	void NameSpace::operator=(NameSpace&& pNameSpace) noexcept
	{
		m_records = std::move(pNameSpace.m_records);
		m_functions = std::move(pNameSpace.m_functions);
	}


	void NameSpace::addFunction(const Function& pFunction)
	{
		m_functions->emplace(pFunction.getFunctionName(), pFunction);
	}


	void NameSpace::addRecord(const Function& pFunction)
	{
		Record::addFunction(pFunction, *m_records.get());
	}


	std::optional<Record> NameSpace::getRecord(const std::string& pRecord)
	{
		const auto& itr = m_records->find(pRecord);
		if (itr != m_records->end()) {
			return std::optional(itr->second);
		}
		return std::nullopt;
	}


	std::optional<Function> NameSpace::getFunction(const std::string& pFunction)
	{
		const auto& itr = m_functions->find(pFunction);
		if (itr != m_functions->end()) {
			return std::optional(itr->second);
		}
		return std::nullopt;
	}


	void NameSpace::init(const std::vector<Function>& pFunctions, std::unordered_map<std::string, NameSpace>& pNamespaces)
	{
		for (const auto& function : pFunctions)
		{
			const auto& nameSpace = function.getNamespace();
			const auto& recordName = function.getRecordName();

			const auto& itr0 = pNamespaces.find(nameSpace);
			if (itr0 == pNamespaces.end()) {
				const auto& itr1 = pNamespaces.emplace(nameSpace, NameSpace());
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