#include "Method.h"


namespace rtl {

	namespace access 
	{
		Method::Method(const Function& pFunction)
			:m_function(pFunction)
		{
		}

		MethodInvoker::MethodInvoker(const Function& pFunction, const std::unique_ptr<RObject>& pTarget)
			: m_function(pFunction)
			, m_target(pTarget)
		{
		}

		const MethodInvoker Method::operator()(const std::unique_ptr<RObject>& pTarget) const
		{
			return MethodInvoker(m_function, pTarget);
		}
	}
}