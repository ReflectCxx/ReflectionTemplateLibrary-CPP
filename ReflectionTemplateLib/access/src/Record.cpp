
#include "Record.h"
#include "Method.h"
#include "RStatus.h"
#include "Constants.h"
#include "Instance.h"

namespace rtl {

	namespace access
	{
		Record::Record(const std::string& pRecordName)
			: m_recordName(pRecordName)
		{
		}

		std::unordered_map< std::string, access::Method >& Record::getFunctionsMap() const
		{
			return m_methods;
		}

		std::optional<Method> Record::getMethod(const std::string& pMethod) const
		{
			const auto& itr = m_methods.find(pMethod);
			if (itr != m_methods.end()) {
				return std::optional(itr->second);
			}
			return std::nullopt;
		}


		RStatus Record::clone(Instance& pOther) const
		{
			return RStatus(false);
		}
	}
}