
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


		const std::pair<RStatus, Instance> Record::clone(Instance& pOther) const
		{
			if (pOther.isEmpty()) {
				return std::make_pair(RStatus(Error::EmptyInstance), Instance());
			}

			const std::string& dctor = (m_recordName + Ctor::DCTOR);
			const std::string& copyStr = (m_recordName + Ctor::CTOR_COPY);
			const std::string& constCopyStr = (m_recordName + Ctor::CTOR_CONST_COPY);

			std::optional<Function> destructor = getMethod(dctor);
			std::optional<Function> constCopyCtor = getMethod(constCopyStr);
			
			if (pOther.isConst()) 
			{
				if (constCopyCtor) 
				{
					if (constCopyCtor->getRecordTypeId() != pOther.getTypeId()) {
						return std::make_pair(RStatus(Error::InstanceTypeMismatch), Instance());
					}
					RStatus status = (*constCopyCtor)(pOther.get());
					return std::make_pair(status, Instance(status.getReturn(), status, *destructor));
				}
				else {
					return std::make_pair(RStatus(Error::ConstCopyConstructorNotFound), Instance());
				}
			}
			else {
				std::optional<Function> copyCtor = getMethod(copyStr);
				if (copyCtor) 
				{
					if (copyCtor->getRecordTypeId() != pOther.getTypeId()) {
						return std::make_pair(RStatus(Error::InstanceTypeMismatch), Instance());
					}
					RStatus status = (*copyCtor)(pOther.get());
					return std::make_pair(status, Instance(status.getReturn(), status, *destructor));
				}
				else if (constCopyCtor) 
				{
					if (constCopyCtor->getRecordTypeId() != pOther.getTypeId()) {
						return std::make_pair(RStatus(Error::InstanceTypeMismatch), Instance());
					}
					RStatus status = (*constCopyCtor)(pOther.get());
					return std::make_pair(status, Instance(status.getReturn(), status, *destructor));
				}
			}
			return std::make_pair(RStatus(Error::CopyConstructorNotFound), Instance());
		}
	}
}