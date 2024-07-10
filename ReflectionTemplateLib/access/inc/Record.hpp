#include <cassert>

#include "Record.h"
#include "RStatus.h"
#include "Method.h"
#include "Constants.h"

namespace rtl {

	namespace access
	{
		template<class ..._ctorArgs>
		inline const std::pair<RStatus, Instance> Record::instance(_ctorArgs ...params) const
		{
			const std::string& ctor = (m_recordName + Member::CTOR);
			const auto& itr = m_methods.find(ctor);
			if (itr != m_methods.end()) {
				const RStatus& status = itr->second.invokeCtor(params...);
				if (status) {
					const std::string& dctor = (m_recordName + Member::DCTOR);
					return std::make_pair(status, Instance(status.getReturn(), status, *getMethod(dctor)));
				}
			}
			else {
				assert(false && "constructor with the given args, not found.");
			}
			return std::make_pair(RStatus(false), Instance());
		}
	}
}