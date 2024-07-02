#pragma once

#include "Function.h"

namespace rtl {

	namespace access
	{
		class Record;

		template<class _targetType>
		class MethodInvoker;

		class Method
		{
			const Function& m_function;

			Method(const Function& pFunction);

		public:

			const MethodInvoker<UniqueAny> operator()(UniqueAny& pTarget) const;

			const MethodInvoker<const UniqueAny> operator()(const UniqueAny& pTarget) const;

			friend Record;
		};


		template<class _targetType>
		class MethodInvoker
		{
			_targetType& m_target;
			const Function& m_function;

			MethodInvoker(const Function& pFunction, _targetType& pTarget);

		public:

			template<class ..._args>
			RStatus invoke(_args...params) const noexcept;

			friend Method;
		};
	}
}