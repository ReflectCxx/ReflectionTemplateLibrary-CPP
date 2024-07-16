
#include "Record.h"
#include "RStatus.h"
#include "Method.h"
#include "Constants.h"
#include "Constants.hpp"
#include "Instance.h"

namespace rtl {

	namespace access
	{
		template<class ..._ctorArgs>
		inline const std::pair<RStatus, Instance> Record::instance(_ctorArgs ...params) const
		{
			const std::string& ctor = getCtorName(m_recordName);
			const auto& itr = m_methods.find(ctor);
			if (itr != m_methods.end()) {
				const RStatus& status = itr->second.invokeCtor(params...);
				if (status) {
					const std::string& dctor = getDctorName(m_recordName);
					return std::make_pair(status, Instance(status.getReturn(), status, *getMethod(dctor)));
				}
				return std::make_pair(status, Instance());
			}
			else {
				return std::make_pair(RStatus(Error::ConstructorNotFound), Instance());
			}
		}
	}
}