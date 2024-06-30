
#include "Record.h"
#include "Method.h"
#include "Constants.h"

namespace rtl {

	namespace access 
	{
		Record::Record(const std::string& pRecordName)
			: m_recordName(pRecordName)
		{
		}

		std::unordered_map <std::string, access::Function>& Record::getFunctionsMap() const
		{
			return m_functions;
		}

		std::optional<Method> Record::getMethod(const std::string& pMethod) const
		{
			const auto& itr = m_functions.find(pMethod);
			if (itr != m_functions.end()) {
				return std::optional(Method(itr->second));
			}
			return std::nullopt;
		}
	}
}