#pragma once
#include "Proxy.h"

namespace proxy_test
{
	template<class ..._args>
	inline std::any Proxy::forwardCall(const std::string& pFunctionName, _args ...params)
	{
		const auto orgMethod = OriginalReflection::obj().classRef()->getMethod(pFunctionName);
		if (orgMethod.has_value() && orgMethod->hasSignature<_args...>()) {
			const auto& retVal = orgMethod->on(m_originalObj).call(params...);
			return retVal.getReturn();
		}
		return std::any();
	}

	template<class ..._args>
	inline static std::any Proxy::forwardStaticCall(const std::string& pFunctionName, _args ...params)
	{
		const auto orgMethod = OriginalReflection::obj().classRef()->getMethod(pFunctionName);
		if (orgMethod.has_value() && orgMethod->hasSignature<_args...>()) {
			const auto& retVal = orgMethod->on().call(params...);
			return retVal.getReturn();
		}
		return std::any();
	}
}