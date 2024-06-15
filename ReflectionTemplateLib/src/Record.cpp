#include "Record.h"

namespace rtl {

	Record::Record()
	: m_functions(new FunctionMap())
	{
	}


	Record::Record(const Record& pRecord)
		: m_functions(pRecord.m_functions)
	{
	}


	Record::Record(Record&& pRecord) noexcept
		: m_functions(std::move(pRecord.m_functions))
	{
	}


	void Record::operator=(Record&& pRecord) noexcept
	{
		m_functions = std::move(pRecord.m_functions);
	}


	void Record::operator=(const Record& pRecord)
	{
		if (this == &pRecord) {
			return;
		}
		m_functions = pRecord.m_functions;
	}


	void Record::addFunction(const Function& pFunction)
	{
		m_functions->emplace(pFunction.getFunctionName(), pFunction);
	}


	std::optional<Function> Record::getFunction(const std::string& pFunction)
	{
		const auto& itr = m_functions->find(pFunction);
		if (itr != m_functions->end()) {
			return std::optional(itr->second);
		}
		return std::nullopt;
	}


	void Record::addFunction(const Function& pFunction, std::unordered_map<std::string, Record>& pRecordMap)
	{
		const auto& recordName = pFunction.getRecordName();
		const auto& itr0 = pRecordMap.find(recordName);
		if (itr0 == pRecordMap.end()) {
			const auto& itr1 = pRecordMap.emplace(recordName, Record());
			itr1.first->second.addFunction(pFunction);
		}
		else {
			itr0->second.addFunction(pFunction);
		}
	}
}