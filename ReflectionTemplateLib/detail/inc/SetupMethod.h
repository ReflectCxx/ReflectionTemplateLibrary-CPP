#pragma once

#include "FunctorId.h"

namespace rtl {

	namespace detail 
	{
		template<class _derivedType>
		class SetupMethod 
		{
			template<class _recordType, class _returnType>
			static const std::size_t getHashCode(const std::size_t pContainerId, const std::size_t pIndex);

		protected:

			template<class _recordType, class _returnType, class ..._signature>
			static const detail::FunctorId pushBack(_returnType(_recordType::* pFunctor)(_signature...),
								enable_if_same<_returnType, void> *_ = nullptr);

			template<class _recordType, class _returnType, class ..._signature>
			static const detail::FunctorId pushBack(_returnType(_recordType::* pFunctor)(_signature...),
								enable_if_notSame<_returnType, void> *_ = nullptr);

			template<class _recordType, class _returnType, class ..._signature>
			static const detail::FunctorId pushBack(_returnType(_recordType::* pFunctor)(_signature...) const,
								enable_if_same<_returnType, void> *_ = nullptr);

			template<class _recordType, class _returnType, class ..._signature>
			static const detail::FunctorId pushBack(_returnType(_recordType::* pFunctor)(_signature...) const,
								enable_if_notSame<_returnType, void> *_ = nullptr);
		};
	}
}