#pragma once

#include <functional>

#include "Function.h"

namespace rtl {

	namespace access
	{
		class Record;
		class Instance;

		class Method : public Function
		{
			Method(const Function& pFunction);

			Method(const Function& pFunction, const detail::FunctorId& pFunctorId);

			template<class ..._args>
			RStatus invokeCtor(_args...params) const;

			template<class ..._args>
			RStatus invoke(const Instance& pTarget, _args...params) const;

			template<class ..._args>
			RStatus invokeConst(const Instance& pTarget, _args...params) const;

		public:

			template<class _arg0, class ..._args>
			const bool hasSignature() const;

			constexpr auto operator()() const
			{
				return [this](auto...params) {
					return Function::operator()(params...);
				};
			}

			constexpr auto operator()(const Instance& pTarget) const
			{
				return [&](auto...params)->RStatus
				{
					switch (pTarget.getQualifier())
					{
					case TypeQ::Mute: return invoke(pTarget, params...);
					case TypeQ::Const: return invokeConst(pTarget, params...);
					}
					return RStatus(false);
				};
			}

			friend Record;
			friend detail::CxxReflection;

			template<class ..._args>
			RStatus operator()(_args...) const noexcept = delete;
		};
	}
}