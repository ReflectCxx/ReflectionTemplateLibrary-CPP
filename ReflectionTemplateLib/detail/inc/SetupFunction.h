#pragma once

#include "FunctorId.h"

namespace rtl {

	namespace detail
	{
		template<class _derivedType>
		class SetupFunction
		{
			template<class _returnType>
			static const std::size_t getHashCode(const std::size_t pContainerId, const std::size_t pIndex,
							     const std::size_t pArgsCount);

		protected:

			template<class _returnType, class ..._signature>
			static const detail::FunctorId pushBack(_returnType(*pFunctor)(_signature...),
								enable_if_void<_returnType> *_ = nullptr);

			template<class _returnType, class ..._signature>
			static const detail::FunctorId pushBack(_returnType(*pFunctor)(_signature...),
								enable_if_non_void<_returnType> *_ = nullptr);
		};
	}
}