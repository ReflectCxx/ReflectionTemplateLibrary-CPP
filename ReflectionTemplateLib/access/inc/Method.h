#pragma once

#include "Function.h"

namespace rtl {

	namespace detail {
		class CxxReflection;
	}

	namespace access
	{
		class Record;
		class Method;
		class UniqueAny;

		class MethodInvoker
		{
			const Method& m_method;
			const UniqueAny& m_target;

			MethodInvoker(const Method& pMethod, const UniqueAny& pTarget);

		public: friend Method;

			template<class ..._args>
			RStatus operator()(_args...params) const noexcept;
		};


		class StaticMethodInvoker
		{
			const Method& m_method;

			StaticMethodInvoker(const Method& pFunction);

		public: friend Method;

			template<class ..._args>
			RStatus operator()(_args...params) const noexcept;
		};


		class Method : public Function
		{
			Method(const Function& pFunction);

			template<class ..._args>
			RStatus invokeCtor(_args...params) const;

			template<class ..._args>
			RStatus invokeStatic(_args...params) const;

			template<class ..._args>
			RStatus invoke(const UniqueAny& pTarget, _args...params) const;

			template<class ..._args>
			RStatus invokeConst(const UniqueAny& pTarget, _args...params) const;

			template<class ..._args>
			RStatus operator()(_args...params) const noexcept = delete;

		public:
			
			const StaticMethodInvoker operator()() const;

			const MethodInvoker operator()(const UniqueAny& pTarget) const;

			template<class _arg0, class ..._args>
			const bool hasSignature() const;

			friend Record;
			friend MethodInvoker;
			friend StaticMethodInvoker;
			friend detail::CxxReflection;
		};
	}
}