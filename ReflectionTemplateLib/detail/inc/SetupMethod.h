#pragma once

#include "Constants.h"

namespace rtl {

	namespace detail 
	{
		template<class _derivedType>
		class SetupMethod 
		{
		protected:

			template<class _recordType, class _returnType, class ..._signature>
			static int addMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...), enable_if_same<_returnType, void> *_ = nullptr);

			template<class _recordType, class _returnType, class ..._signature>
			static int addMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...), enable_if_notSame<_returnType, void> *_ = nullptr);
		};		
	}
}