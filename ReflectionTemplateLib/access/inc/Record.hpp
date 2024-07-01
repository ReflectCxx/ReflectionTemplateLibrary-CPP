
#include <cassert>

#include "Record.h"
#include "RStatus.h"
#include "Function.h"
#include "Constants.h"

namespace rtl {

	namespace access 
	{
		template<class ..._ctorArgs>
		inline RStatus Record::instance(_ctorArgs ...params) const
		{
			const auto& ctorName = (m_recordName + CTOR_SUFFIX);
			const auto& itr = m_functions->find(ctorName);
			if (itr != m_functions->end()) {
				return itr->second.invokeConstructor(params...);
			}
			else {
				assert(false && "Throw bad call exception");
			}
			return RStatus(false);
		}
	}
}