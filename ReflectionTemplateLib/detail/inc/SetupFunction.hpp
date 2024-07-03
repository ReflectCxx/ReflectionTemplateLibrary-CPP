
#include "RStatus.h"
#include "SetupFunction.h"

namespace rtl
{
	namespace detail
	{
		template<class _derivedType>
		template<class _returnType>
		inline const std::size_t SetupFunction<_derivedType>::getHashCode(const std::size_t pContainerId, const std::size_t pIndex)
		{
			return std::stoull(std::to_string(TypeId<_returnType>::get()) + std::to_string(pContainerId) + std::to_string(pIndex));
		}


		template<class _derivedType>
		template<class _returnType, class ..._signature>
		inline const access::FunctorId SetupFunction<_derivedType>::pushBack(_returnType(*pFunctor)(_signature...),
										     enable_if_same<_returnType, void> *_)
		{
			const auto functor = [=](_signature...params)->access::RStatus
			{
				(*pFunctor)(params...);
				return access::RStatus(true);
			};

			auto& functors = _derivedType::getFunctors();
			const std::size_t& index = functors.size();
			const std::size_t& hashCode = getHashCode<_returnType>(_derivedType::getContainerId(), index);
			functors.push_back(std::make_pair(hashCode, functor));
			return access::FunctorId(index, hashCode, _derivedType::getContainerId());
		}


		template<class _derivedType>
		template<class _returnType, class ..._signature>
		inline const access::FunctorId SetupFunction<_derivedType>::pushBack(_returnType(*pFunctor)(_signature...),
										     enable_if_notSame<_returnType, void> *_)
		{
			const auto functor = [=](_signature...params)->access::RStatus
			{
				const auto& typeId = TypeId<_returnType>::get();
				const _returnType& retObj = (*pFunctor)(params...);
				const TypeQ& qualifier = std::is_const<_returnType>::value ? TypeQ::Const : TypeQ::Vol;
				return access::RStatus(true, std::make_any<_returnType>(retObj), typeId, qualifier);
			};

			auto& functors = _derivedType::getFunctors();
			const std::size_t& index = functors.size();
			const std::size_t& hashCode = getHashCode<_returnType>(_derivedType::getContainerId(), index);
			functors.push_back(std::make_pair(hashCode, functor));
			return access::FunctorId(index, hashCode, _derivedType::getContainerId());
		}
	}
}