#pragma once

#include "Function.h"
#include "RObject.hpp"

namespace rtl {

	namespace access
	{
		class Record;
		class MethodInvoker;

		class Method
		{
			friend Record;

			const Function& m_function;

			Method(const Function& pFunction);

		public:

			const MethodInvoker operator()(const std::unique_ptr<RObject>& pTarget) const;
		};


		class MethodInvoker
		{
			friend Method;

			const Function& m_function;
			const std::unique_ptr<RObject>& m_target;

			MethodInvoker(const Function& pFunction, const std::unique_ptr<RObject>& pTarget);

		public:
			
			template<class ..._args>
			std::unique_ptr<RObject> invoke(_args...params) const;
		};
	}
}