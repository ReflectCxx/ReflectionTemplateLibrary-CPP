#pragma once

#include "Function.h"

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

			const MethodInvoker operator()(const Rany& pTarget) const;
		};


		class MethodInvoker
		{
			friend Method;

			const Rany& m_target;
			const Function& m_function;

			MethodInvoker(const Function& pFunction, const Rany& pTarget);

		public:
			
			template<class ..._args>
			Rany invoke(_args...params) const noexcept;
		};
	}
}