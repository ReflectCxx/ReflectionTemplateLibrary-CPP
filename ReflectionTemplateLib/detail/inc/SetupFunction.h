#pragma once

#include "Constants.h"

namespace rtl {

	namespace detail
	{
		template<class _derivedType>
		class SetupFunction
		{
		protected:

			template<class _returnType, class ..._signature>
			static int addFunctor(_returnType(*pFunctor)(_signature...), enable_if_same<_returnType, void> *_ = nullptr);

			template<class _returnType, class ..._signature>
			static int addFunctor(_returnType(*pFunctor)(_signature...), enable_if_notSame<_returnType, void> *_ = nullptr);
		};
	}
}