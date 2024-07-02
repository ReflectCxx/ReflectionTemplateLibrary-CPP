
#include "RStatus.h"
#include "SetupFunction.h"

namespace rtl
{
	namespace detail
	{
		template<class _derivedType>
		template<class _returnType, class ..._signature>
		inline int SetupFunction<_derivedType>::addFunctor(_returnType(*pFunctor)(_signature...), enable_if_same<_returnType, void> *_)
		{
			const auto functor = [=](_signature...params)->access::RStatus
			{
				(*pFunctor)(params...);
				return access::RStatus(true);
			};

			auto& functors = _derivedType::getFunctors();
			functors.push_back(functor);
			return (functors.size() - 1);
		}


		template<class _derivedType>
		template<class _returnType, class ..._signature>
		inline int SetupFunction<_derivedType>::addFunctor(_returnType(*pFunctor)(_signature...), enable_if_notSame<_returnType, void> *_)
		{
			const auto functor = [=](_signature...params)->access::RStatus
			{
				const auto& typeId = TypeId<_returnType>::get();
				const _returnType& retObj = (*pFunctor)(params...);
				return access::RStatus(true, std::make_any<_returnType>(retObj), typeId);
			};

			auto& functors = _derivedType::getFunctors();
			functors.push_back(functor);
			return (functors.size() - 1);
		}
	}
}