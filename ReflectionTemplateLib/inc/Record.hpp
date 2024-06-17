
#include <cassert>

#include "Record.h"
#include "Constants.h"

namespace rtl {

	template<class ..._ctorArgs>
	inline void Record::newInstance(_ctorArgs ...params) const
	{
		const auto& signatureId = FunctorContainer<_ctorArgs...>::getContainerId();
		const auto& ctorName = (m_recordName + CTOR_SUFFIX + std::to_string(signatureId));
		const auto& itr = m_constructors->find(ctorName);

		if (itr != m_constructors->end()) {
			itr->second.execute(params...);
		}
		else {
			assert(false && "Throw bad call exception");
		}
	}
}