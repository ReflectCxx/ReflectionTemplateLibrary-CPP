
#include "RStatus.h"
#include "SetupFunction.h"

namespace rtl
{
	namespace detail
	{
		template<class _derivedType>
		template<class _returnType, class ..._signature>
		inline const detail::FunctorId SetupFunction<_derivedType>::addFunctor(_returnType(*pFunctor)(_signature...),
										       enable_if_void<_returnType> *_)
		{
			const auto functor = [=](_signature...params)->access::RStatus
			{
				(*pFunctor)(params...);
				return access::RStatus(Error::None);
			};

			const std::size_t& index = _derivedType::pushBack(functor);
			return detail::FunctorId(index, TypeId<_returnType>::get(), TypeId<>::None, _derivedType::getContainerId());
		}


		template<class _derivedType>
		template<class _returnType, class ..._signature>
		inline const detail::FunctorId SetupFunction<_derivedType>::addFunctor(_returnType(*pFunctor)(_signature...),
										       enable_if_non_void<_returnType> *_)
		{
			const auto& typeId = TypeId<_returnType>::get();
			const auto functor = [=](_signature...params)->access::RStatus
			{
				const _returnType& retObj = (*pFunctor)(params...);
				const TypeQ& qualifier = std::is_const<_returnType>::value ? TypeQ::Const : TypeQ::Mute;
				return access::RStatus(std::make_any<_returnType>(retObj), typeId, qualifier);
			};

			const std::size_t& index = _derivedType::pushBack(functor);
			return detail::FunctorId(index, TypeId<_returnType>::get(), TypeId<>::None, _derivedType::getContainerId());
		}
	}
}