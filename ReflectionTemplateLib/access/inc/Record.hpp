#include <cassert>

#include "Record.h"
#include "RStatus.h"
#include "Method.h"
#include "Constants.h"

namespace rtl {

	namespace access
	{
		template<class ..._ctorArgs>
		inline RStatus Record::instance(_ctorArgs ...params) const
		{
			const auto& ctorName = (m_recordName + CTOR_SUFFIX);
			const auto& itr = m_methods.find(ctorName);
			if (itr != m_methods.end()) {
				return itr->second.invokeCtor(params...);
			}
			else {
				assert(false && "constructor with the given args, not found.");
			}
			return RStatus(false);
		}
	}
}