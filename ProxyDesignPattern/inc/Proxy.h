#pragma once

#include <any>
#include <optional>

#include "OrgReflection.h"

namespace proxy_test {

	class Proxy
	{
		OrgReflection m_reflection;
		std::optional<rtl::access::Record> m_originalClass;
		rtl::access::Instance m_originalObj;

	public:

		Proxy();

		template<class ..._args>
		std::any forwardCall(const std::string& pFunctionName, _args ...params) 
		{
			const auto orgMethod = m_originalClass->getMethod(pFunctionName);
			if (orgMethod.has_value() && orgMethod->hasSignature<_args...>()) {
				const auto& retVal = orgMethod->on(m_originalObj).call(params...);
				return retVal.getReturn();
			}
			return std::any();
		}
	};
}