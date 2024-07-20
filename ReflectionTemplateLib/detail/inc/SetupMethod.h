#pragma once

#include "FunctorId.h"

namespace rtl {

	namespace detail
	{
		template<class _derivedType>
		class SetupMethod
		{
		protected:

			template<class _recordType, class _retType, class ..._signature>
			static const detail::FunctorId addFunctor(_retType(_recordType::* pFunctor)(_signature...));

			template<class _recordType, class _retType, class ..._signature>
			static const detail::FunctorId addFunctor(_retType(_recordType::* pFunctor)(_signature...) const);
		};
	}
}