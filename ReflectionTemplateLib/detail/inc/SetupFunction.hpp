
#include "RStatus.h"
#include "SetupFunction.h"

namespace rtl
{
	namespace detail
	{
		template<class _derivedType>
		template<class _returnType>
		inline const std::size_t SetupFunction<_derivedType>::getHashCode(const std::size_t pContainerId, const std::size_t pIndex,
										  const std::size_t pArgsCount)
		{
			return std::stoull(std::to_string(pContainerId) + std::to_string(pIndex) +
					   std::to_string(TypeId<_returnType>::get()) + std::to_string(pArgsCount));
		}


		template<class _derivedType>
		template<class _returnType, class ..._signature>
		inline const detail::FunctorId SetupFunction<_derivedType>::pushBack(_returnType(*pFunctor)(_signature...),
										     enable_if_void<_returnType> *_)
		{
			const auto functor = [=](_signature...params)->access::RStatus
			{
				(*pFunctor)(params...);
				return access::RStatus(Error::None);
			};

			auto& functors = _derivedType::getFunctors();
			const std::size_t& index = functors.size();
			const std::size_t& argsCount = sizeof...(_signature);
			const std::size_t& hashCode = getHashCode<_returnType>(_derivedType::getContainerId(), index, argsCount);
			functors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId(), argsCount, FunctorType::Function);
		}


		template<class _derivedType>
		template<class _returnType, class ..._signature>
		inline const detail::FunctorId SetupFunction<_derivedType>::pushBack(_returnType(*pFunctor)(_signature...),
										     enable_if_non_void<_returnType> *_)
		{
			const auto& typeId = TypeId<_returnType>::get();
			const auto& constTypeId = TypeId<const _returnType>::get();
			const auto functor = [=](_signature...params)->access::RStatus
			{
				const _returnType& retObj = (*pFunctor)(params...);
				const TypeQ& qualifier = std::is_const<_returnType>::value ? TypeQ::Const : TypeQ::Mute;
				return access::RStatus(std::make_any<_returnType>(retObj), typeId, constTypeId, qualifier);
			};

			auto& functors = _derivedType::getFunctors();
			const std::size_t& index = functors.size();
			const std::size_t& argsCount = sizeof...(_signature);
			const std::size_t& hashCode = getHashCode<_returnType>(_derivedType::getContainerId(), index, argsCount);
			functors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId(), argsCount, FunctorType::Function);
		}
	}
}