#pragma once

#include <functional>

#include "Function.h"

namespace rtl {

	namespace detail {
		class CxxReflection;
	}

	namespace access
	{
		class Record;
		class UniqueAny;

		class Method : public Function
		{
			Method(const Function& pFunction);

			template<class ..._args>
			RStatus invokeCtor(_args...params) const;

			template<class ..._args>
			RStatus invoke(const UniqueAny& pTarget, _args...params) const;

			template<class ..._args>
			RStatus invokeConst(const UniqueAny& pTarget, _args...params) const;

		public:

			template<class _arg0, class ..._args>
			const bool hasSignature() const;

			auto operator()() const
			{
				return [this](auto...params) {
					return Function::operator()(params...);
				};
			}

			auto operator()(const UniqueAny& pTarget) const
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
			RStatus operator()(_args...params) const noexcept = delete;
		};
	}
}