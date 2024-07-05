#pragma once

#include "Function.h"

namespace rtl {

	namespace detail {
		class CxxReflection;
	}

	namespace access
	{
		class Record;
		class UniqueAny;
		class MethodInvoker;

		class Method : public Function
		{
			Method(const Function& pFunction);

			template<class ..._args>
			RStatus invokeConstructor(_args...params) const;

			template<class ..._args>
			RStatus invokeMethod(const UniqueAny& pTarget, _args...params) const;

			template<class ..._args>
			RStatus invokeConstMethod(const UniqueAny& pTarget, _args...params) const;

		public:
			
			template<class ..._args>
			RStatus operator()(_args...params) const noexcept = delete;

			const MethodInvoker operator()(const UniqueAny& pTarget) const;

			template<class _arg0, class ..._args>
			const bool hasSignature() const;

			friend Record;
			friend MethodInvoker;
			friend detail::CxxReflection;
		};


		class MethodInvoker
		{
			const Method& m_method;
			const UniqueAny& m_target;

			MethodInvoker(const Method& pFunction, const UniqueAny& pTarget);

		public:

			template<class ..._args>
			RStatus operator()(_args...params) const noexcept;

			friend Method;
		};
	}
}