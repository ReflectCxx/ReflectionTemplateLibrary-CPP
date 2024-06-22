#include "Method.h"

namespace rtl {

	namespace access 
	{
		template<class ..._args>
		inline std::unique_ptr<RObject> MethodInvoker::invoke(_args ...params) const
		{
			return m_function(m_target, params...);
		}
	}
}