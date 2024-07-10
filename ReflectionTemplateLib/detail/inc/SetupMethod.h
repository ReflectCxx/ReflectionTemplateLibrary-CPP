#pragma once

#include "FunctorId.h"

namespace rtl {

	namespace detail 
	{
		template<class _derivedType>
		class SetupMethod 
		{
			template<class _recordType, class _retType>
			static const std::size_t getHashCode(const std::size_t pContainerId, const std::size_t pIndex,
							     const std::size_t pArgsCount);

		protected:

			template<class _recordType, class _retType, class ..._signature>
			static const detail::FunctorId pushBack(_retType(_recordType::* pFunctor)(_signature...),
								enable_if_void<_retType> *_= nullptr);

			template<class _recordType, class _retType, class ..._signature>
			static const detail::FunctorId pushBack(_retType(_recordType::* pFunctor)(_signature...),
								enable_if_non_void<_retType> *_= nullptr);

			template<class _recordType, class _retType, class ..._signature>
			static const detail::FunctorId pushBack(_retType(_recordType::* pFunctor)(_signature...) const,
								enable_if_void<_retType> *_= nullptr);

			template<class _recordType, class _retType, class ..._signature>
			static const detail::FunctorId pushBack(_retType(_recordType::* pFunctor)(_signature...) const,
								enable_if_non_void<_retType> *_= nullptr);
		};
	}
}