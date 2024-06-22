
#include <cassert>

#include "Record.h"
#include "Function.h"
#include "Constants.h"
#include "FunctorContainer.hpp"

namespace rtl {

	namespace access 
	{
		template<class ..._ctorArgs>
		inline std::unique_ptr<RObject> Record::newInstance(_ctorArgs ...params) const
		{
			const auto& signatureId = FunctorContainer<_ctorArgs...>::getContainerId();
			const auto& ctorName = (m_recordName + CTOR_SUFFIX + std::to_string(signatureId));
			const auto& itr = m_constructors->find(ctorName);

			if (itr != m_constructors->end()) {
				return itr->second.execute(params...);
			}
			else {
				assert(false && "Throw bad call exception");
			}
			return nullptr;
		}
	}
}