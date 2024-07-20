#pragma once

#include "RStatus.h"
#include "TypeId.hpp"
#include "SetupMethod.h"

namespace rtl
{
	namespace detail
	{
		template<class _derivedType>
		template<class _recordType, class _retType, class ..._signature>
		inline const detail::FunctorId SetupMethod<_derivedType>::addFunctor(_retType(_recordType::* pFunctor)(_signature...))
		{
			static std::vector<std::pair<decltype(pFunctor), std::size_t>> functorSet;
			const auto& updateIndex = [&](const std::size_t& pIndex) {
				functorSet.emplace_back(pFunctor, pIndex);
			};
			const auto& getIndex = [&]()->const std::size_t {
				for (const auto& fptr : functorSet) {
					if (fptr.first == pFunctor) {
						return fptr.second;
					}
				}
				return -1;
			};

			const std::size_t retTypeId = TypeId<_retType>::get();
			const auto functor = [=](const std::any& pTargetObj, _signature...params)->access::RStatus
			{
				_recordType* target = std::any_cast<_recordType*>(pTargetObj);

				if constexpr (std::is_same_v<_retType, void>) {
					(target->*pFunctor)(params...);
					return access::RStatus(Error::None);
				}
				else {
					const _retType& retObj = (target->*pFunctor)(params...);
					const TypeQ& qualifier = std::is_const<_retType>::value ? TypeQ::Const : TypeQ::Mute;
					return access::RStatus(std::make_any<_retType>(retObj), retTypeId, qualifier);
				}
			};

			const std::size_t& index = _derivedType::pushBack(functor, getIndex, updateIndex);
			return detail::FunctorId(index, retTypeId, TypeId<_recordType>::get(), _derivedType::getContainerId(),
				_derivedType::template getSignatureStr<_recordType, _retType>());
		}


		template<class _derivedType>
		template<class _recordType, class _retType, class ..._signature>
		inline const detail::FunctorId SetupMethod<_derivedType>::addFunctor(_retType(_recordType::* pFunctor)(_signature...) const)
		{
			static std::vector<std::pair<decltype(pFunctor), std::size_t>> functorSet;
			const auto& updateIndex = [&](const std::size_t& pIndex) {
				functorSet.emplace_back(pFunctor, pIndex);
			};
			const auto& getIndex = [&]()->const std::size_t {
				for (const auto& fptr : functorSet) {
					if (fptr.first == pFunctor) {
						return fptr.second;
					}
				}
				return -1;
			};

			const std::size_t retTypeId = TypeId<_retType>::get();
			const std::size_t constRetTypeId = TypeId<const _retType>::get();
			const auto functor = [=](const std::any& pTargetObj, _signature...params)->access::RStatus
			{
				_recordType* target = std::any_cast<_recordType*>(pTargetObj);
				if constexpr (std::is_same_v<_retType, void>) {
					((static_cast<const _recordType*>(target))->*pFunctor)(params...);
					return access::RStatus(Error::None);
				}
				else {
					const TypeQ& qualifier = std::is_const<_retType>::value ? TypeQ::Const : TypeQ::Mute;
					const _retType& retObj = ((static_cast<const _recordType*>(target))->*pFunctor)(params...);
					return access::RStatus(std::make_any<_retType>(retObj), retTypeId, constRetTypeId, qualifier);
				}
			};

			const std::size_t& index = _derivedType::pushBack(functor, getIndex, updateIndex);
			return detail::FunctorId(index, retTypeId, TypeId<_recordType>::get(), _derivedType::getContainerId(),
				_derivedType::template getSignatureStr<_recordType, _retType>());
		}
	}
}