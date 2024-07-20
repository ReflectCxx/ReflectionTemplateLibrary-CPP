#pragma once

#include "FunctorId.h"

namespace rtl {

	namespace detail
	{
		template<class _derivedType>
		class SetupFunction
		{
		protected:

			template<class _returnType, class ..._signature>
			static const detail::FunctorId addFunctor(_returnType(*pFunctor)(_signature...));
		};
	}
}