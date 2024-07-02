#include "Method.h"

namespace rtl {

	namespace access
	{
		template<class _targetType>
		inline MethodInvoker<_targetType>::MethodInvoker(const Function& pFunction, _targetType& pTarget)
			: m_function(pFunction)
			, m_target(pTarget) {
		}

		template<class _targetType>
		template<class ..._args>
		inline RStatus MethodInvoker<_targetType>::invoke(_args ...params) const noexcept
		{
			return m_function.invokeMethod(m_target, params...);
		}

		inline const MethodInvoker<UniqueAny> Method::operator()(UniqueAny& pTarget) const
		{
			return MethodInvoker<UniqueAny>(m_function, pTarget);
		}

		inline const MethodInvoker<const UniqueAny> Method::operator()(const UniqueAny& pTarget) const
		{
			return MethodInvoker<const UniqueAny>(m_function, pTarget);
		}
	}
}