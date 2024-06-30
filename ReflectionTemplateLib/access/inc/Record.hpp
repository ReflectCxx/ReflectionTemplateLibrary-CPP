
#include <cassert>

#include "Record.h"
#include "Function.h"
#include "Constants.h"
#include "FunctorContainer.hpp"

namespace rtl {

	namespace access 
	{
		template<class ..._ctorArgs>
		inline SmartAny Record::instance(_ctorArgs ...params) const
		{
			const auto& ctorName = (m_recordName + CTOR_SUFFIX);
			const auto& itr = m_functions.find(ctorName);
			if (itr != m_functions.end()) {
				return itr->second.invokeConstructor(AllocType::Static, params...);
			}
			else {
				assert(false && "Throw bad call exception");
			}
			return SmartAny();
		}


		template<class ..._ctorArgs>
		inline SmartAny Record::newInstance(_ctorArgs ...params) const
		{
			const auto& ctorName = (m_recordName + CTOR_SUFFIX);
			const auto& itr = m_functions.find(ctorName);
			if (itr != m_functions.end()) {
				return itr->second.invokeConstructor(AllocType::Dynamic, params...);
			}
			else {
				assert(false && "Throw bad call exception");
			}
			return SmartAny();
		}
	}
}