#include "Method.h"

namespace rtl {

	namespace access
	{
		inline MethodInvoker::MethodInvoker(const Function& pFunction, const UniqueAny& pTarget)
			: m_function(pFunction)
			, m_target(pTarget) {
		}

		template<class ..._args>
		inline RStatus MethodInvoker::invoke(_args ...params) const noexcept
		{
			if (m_target.getQualifier() == TypeQ::Const) {
				return m_function.invokeConstMethod(m_target, params...);
			}
			else {
				return m_function.invokeMethod(m_target, params...);
			}
		}


		inline const MethodInvoker Method::operator()(const UniqueAny& pTarget) const
		{
			return MethodInvoker(m_function, pTarget);
		}
	}
}