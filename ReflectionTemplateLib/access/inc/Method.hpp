#include "Method.h"

namespace rtl {

	namespace access 
	{
		inline MethodInvoker::MethodInvoker(const Function& pFunction, const std::unique_ptr<RObject>& pTarget)
			: m_function(pFunction)
			, m_target(pTarget) {
		}

		template<class ..._args>
		inline std::unique_ptr<RObject> MethodInvoker::invoke(_args ...params) const noexcept
		{
			return m_function(m_target, params...);
		}

		inline const MethodInvoker Method::operator()(const std::unique_ptr<RObject>& pTarget) const
		{
			return MethodInvoker(m_function, pTarget);
		}
	}
}