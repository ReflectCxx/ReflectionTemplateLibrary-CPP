#pragma once

#include "Function.h"
#include "RObject.hpp"

namespace rtl {

	class Record;
	class MethodInvoker;

	class Method
	{
		const Function& m_function;

		Method(const Function& pFunction);

	public: friend Record;

		const MethodInvoker operator()(const std::unique_ptr<RObject>& pTarget) const;
	};


	class MethodInvoker
	{
		const Function& m_function;
		const std::unique_ptr<RObject>& m_target;

		MethodInvoker(const Function& pFunction, const std::unique_ptr<RObject>& pTarget);

	public: friend Method;
		
		template<class ..._args>
		std::unique_ptr<RObject> invoke(_args...params) const;
	};
}