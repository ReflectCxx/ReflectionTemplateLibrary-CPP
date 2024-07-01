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

			const MethodInvoker operator()(const UniqueAny& pTarget) const;

			friend Record;
		};


		class MethodInvoker
		{
			const UniqueAny& m_target;
			const Function& m_function;

			MethodInvoker(const Function& pFunction, const UniqueAny& pTarget);

		public:
			
			template<class ..._args>
			RStatus invoke(_args...params) const noexcept;

			friend Method;
		};
	}
}