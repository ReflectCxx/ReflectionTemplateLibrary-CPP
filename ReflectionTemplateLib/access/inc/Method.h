#pragma once

#include "Function.h"

namespace rtl {

	namespace access
	{
		class Record;
		class MethodInvoker;

		class Method
		{
			const Function& m_function;

			Method(const Function& pFunction);

		public:

			const MethodInvoker operator()(const SmartAny& pTarget) const;

			friend Record;
		};


		class MethodInvoker
		{
			const SmartAny& m_target;
			const Function& m_function;

			MethodInvoker(const Function& pFunction, const SmartAny& pTarget);

		public:
			
			template<class ..._args>
			RStatus invoke(_args...params) const noexcept;

			friend Method;
		};
	}
}