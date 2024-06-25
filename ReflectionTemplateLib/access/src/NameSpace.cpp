
#include "Record.h"
#include "Function.h"
#include "NameSpace.h"

namespace rtl {

	namespace access 
	{
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
			if (this == &pNameSpace) {
				return;
			}
			m_records = std::move(pNameSpace.m_records);
			m_functions = std::move(pNameSpace.m_functions);
		}


		void NameSpace::addFunction(const Function& pFunction)
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


		void NameSpace::init() const
		{
			for (const auto& itr : *m_functions)
			{
				const Function& function = itr.second;
				function.sortFunctorsHash();
			}

			for (const auto& itr : *m_records)
			{
				const Record& record = itr.second;
				record.init();
			}
		}
	}
}