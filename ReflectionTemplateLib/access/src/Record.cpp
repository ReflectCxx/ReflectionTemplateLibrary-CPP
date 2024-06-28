
#include "Record.h"
#include "Method.h"
#include "Constants.h"

namespace rtl {

	namespace access 
	{
		Record::Record(const std::string& pRecordName)
			: m_recordName(pRecordName)
			, m_functions(new FunctionMap())
		{
		}


		Record::Record(const Record& pRecord)
			: m_recordName(pRecord.m_recordName)
			, m_functions(pRecord.m_functions)
		{
		}


		Record::Record(Record&& pRecord) noexcept
			: m_recordName(std::move(pRecord.m_recordName))
			, m_functions(std::move(pRecord.m_functions))
		{
		}


		void Record::operator=(Record&& pRecord) noexcept
		{
			if (this == &pRecord) {
				return;
			}
			m_recordName = std::move(pRecord.m_recordName);
			m_functions = std::move(pRecord.m_functions);
		}

		void Record::operator=(const Record& pRecord)
		{
			if (this == &pRecord) {
				return;
			}
			m_recordName = pRecord.m_recordName;
			m_functions = pRecord.m_functions;
		}


		void Record::init() const
		{
			for (const auto& itr : *m_functions) 
			{
				const Function& function = itr.second;
				function.sortFunctorsHash();
			}
		}


		std::optional<Method> Record::getMethod(const std::string& pMethod) const
		{
			const auto& itr = m_functions->find(pMethod);
			if (itr != m_functions->end()) {
				return std::optional(Method(itr->second));
			}
			return std::nullopt;
		}


		void Record::addFunction(const Function& pFunction) const
		{
			const auto& funcName = pFunction.getFunctionName();
			const auto& itr = m_functions->find(funcName);
			if (itr == m_functions->end()) {
				m_functions->emplace(pFunction.getFunctionName(), pFunction);
			}
			else {
				const auto& function = itr->second;
				function.addOverload(pFunction);
			}
		}


		void Record::addFunction(const Function& pFunction, std::unordered_map<std::string, Record>& pRecordMap)
		{
			const auto& recordName = pFunction.getRecordName();
			const auto& itr0 = pRecordMap.find(recordName);
			if (itr0 == pRecordMap.end()) {
				const auto& itr1 = pRecordMap.emplace(recordName, Record(recordName));
				itr1.first->second.addFunction(pFunction);
			}
			else {
				itr0->second.addFunction(pFunction);
			}
		}
	}
}