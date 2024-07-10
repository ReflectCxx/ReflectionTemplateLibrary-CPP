
#include "Record.h"
#include "Method.h"
#include "RStatus.h"
#include "Instance.h"
#include "Constants.h"
#include "Function.hpp"

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


		std::optional<Instance> Record::clone(Instance& pOther) const
		{
			const std::string& dctor = (m_recordName + Member::DCTOR);
			const std::string& copyStr = (m_recordName + Member::CTOR_COPY);
			const std::string& constCopyStr = (m_recordName + Member::CTOR_CONST_COPY);

			std::optional<Function> destructor = getMethod(dctor);
			std::optional<Function> constCopyCtor = getMethod(constCopyStr);
			
			if (pOther.isConst()) 
			{
				if (constCopyCtor) {
					RStatus status = (*constCopyCtor)(pOther.get());
					return std::make_optional(Instance(status.getReturn(), status, *destructor));
				}
			}
			else {
				std::optional<Function> copyCtor = getMethod(copyStr);
				if (copyCtor) {
					RStatus status = (*copyCtor)(pOther.get());
					if (status) {
						return std::make_optional(Instance(status.getReturn(), status, *destructor));
					}
				}
				else if (constCopyCtor) {
					RStatus status = (*constCopyCtor)(pOther.get());
					if (status) {
						return std::make_optional(Instance(status.getReturn(), status, *destructor));
					}
				}
			}
			return std::nullopt;
		}
	}
}