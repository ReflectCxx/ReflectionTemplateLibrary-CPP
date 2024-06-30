#include "Method.h"

namespace rtl {

	namespace access 
	{
		inline MethodInvoker::MethodInvoker(const Function& pFunction, const SmartAny& pTarget)
			: m_function(pFunction)
			, m_target(pTarget) {
		}

		template<class ..._args>
		inline SmartAny MethodInvoker::invoke(_args ...params) const noexcept
		{
			return m_function.invokeMethod(m_target, params...);
		}

		inline const MethodInvoker Method::operator()(const SmartAny& pTarget) const
		{
			return MethodInvoker(m_function, pTarget);
		}
	}
}