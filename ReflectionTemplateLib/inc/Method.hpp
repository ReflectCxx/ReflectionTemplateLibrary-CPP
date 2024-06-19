#include "Method.h"

namespace rtl {

	template<class ..._args>
	inline std::unique_ptr<RObject> MethodInvoker::invoke(_args ...params) const
	{
		return m_function.execute(m_target, params...);
	}
}