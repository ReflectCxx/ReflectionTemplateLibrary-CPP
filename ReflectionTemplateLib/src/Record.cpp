
#include "Record.h"
#include "RObject.h"
#include "Method.h"
#include "Function.h"
#include "Constants.h"

namespace rtl {

	Record::Record(const std::string& pRecordName)
		: m_recordName(pRecordName)
		, m_functions(new FunctionMap())
		, m_constructors(new FunctionMap())
	{
	}


	Record::Record(const Record& pRecord)
		: m_recordName(pRecord.m_recordName)
		, m_functions(pRecord.m_functions)
		, m_constructors(pRecord.m_constructors)
	{
	}


	Record::Record(Record&& pRecord) noexcept
		: m_recordName(std::move(pRecord.m_recordName))
		, m_functions(std::move(pRecord.m_functions))
		, m_constructors(std::move(pRecord.m_constructors))
	{
	}


	void Record::operator=(Record&& pRecord) noexcept
	{
		if (this == &pRecord) {
			return;
		}
		m_recordName = std::move(pRecord.m_recordName);
		m_functions = std::move(pRecord.m_functions);
		m_constructors = std::move(pRecord.m_constructors);
	}


	std::optional<Method> Record::getMethod(const std::string& pMethod) const
	{
		const auto& itr = m_functions->find(pMethod);
		if (itr != m_functions->end()) {
			return std::optional(Method(itr->second));
		}
		return std::nullopt;
	}


	void Record::operator=(const Record& pRecord)
	{
		if (this == &pRecord) {
			return;
		}
		m_recordName = pRecord.m_recordName;
		m_functions = pRecord.m_functions;
		m_constructors = pRecord.m_constructors;
	}


	void Record::addFunction(const Function& pFunction) const
	{
		m_functions->emplace(pFunction.getFunctionName(), pFunction);
	}


	void Record::addConstructor(const Function& pFunction) const
	{
		m_constructors->emplace(pFunction.getFunctionName(), pFunction);
	}


	void Record::addFunction(const Function& pFunction, std::unordered_map<std::string, Record>& pRecordMap)
	{
		const auto& recordName = pFunction.getRecordName();
		const auto& itr0 = pRecordMap.find(recordName);
		if (itr0 == pRecordMap.end()) {
			const auto& itr1 = pRecordMap.emplace(recordName, Record(recordName));
			if (pFunction.getFunctionName().find(CTOR_SUFFIX) == std::string::npos) {
				itr1.first->second.addFunction(pFunction);
			}
			else {
				itr1.first->second.addConstructor(pFunction);
			}
		}
		else {
			if (pFunction.getFunctionName().find(CTOR_SUFFIX) == std::string::npos) {
				itr0->second.addFunction(pFunction);
			}
			else {
				itr0->second.addConstructor(pFunction);
			}
		}
	}
}