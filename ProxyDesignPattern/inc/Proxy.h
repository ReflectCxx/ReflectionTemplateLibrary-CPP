#pragma once

#include <any>
#include "OriginalReflection.h"

namespace proxy_test {

	class Proxy
	{
		rtl::access::Instance m_originalObj;

	public:

		Proxy();

		template<class ..._args>
		std::any forwardCall(const std::string& pFunctionName, _args ...params);

		template<class ..._args>
		static std::any forwardStaticCall(const std::string& pFunctionName, _args ...params);
	};
}