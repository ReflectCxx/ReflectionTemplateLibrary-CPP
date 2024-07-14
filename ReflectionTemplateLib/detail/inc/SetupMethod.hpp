#pragma once

#include <cassert>

#include "RStatus.h"
#include "TypeId.hpp"
#include "SetupMethod.h"

namespace rtl 
{
	namespace detail
	{
		template<class _derivedType>
		template<class _recordType, class _retType, class ..._signature>
		inline const detail::FunctorId SetupMethod<_derivedType>::addFunctor(_retType(_recordType::* pFunctor)(_signature...),
										     enable_if_void<_retType> *_)
		{
			const auto functor = [=](const std::any& pTargetObj, _signature...params)->access::RStatus
			{
				_recordType* target = std::any_cast<_recordType*>(pTargetObj);
				(target->*pFunctor)(params...);
				return access::RStatus(Error::None);
			};

			const std::size_t& index = _derivedType::pushBack(functor);
			return detail::FunctorId(index, TypeId<_retType>::get(), TypeId<_recordType>::get(), _derivedType::getContainerId());
		}


		template<class _derivedType>
		template<class _recordType, class _retType, class ..._signature>
		inline const detail::FunctorId SetupMethod<_derivedType>::addFunctor(_retType(_recordType::* pFunctor)(_signature...),
										     enable_if_non_void<_retType> *_)
		{
			const std::size_t retTypeId = TypeId<_retType>::get();
			const auto functor = [=](const std::any& pTargetObj, _signature...params)->access::RStatus
			{
				_recordType* target = std::any_cast<_recordType*>(pTargetObj);
				const _retType& retObj = (target->*pFunctor)(params...);
				const TypeQ& qualifier = std::is_const<_retType>::value ? TypeQ::Const : TypeQ::Mute;
				return access::RStatus(std::make_any<_retType>(retObj), retTypeId, qualifier);
			};

			const std::size_t& index = _derivedType::pushBack(functor);
			return detail::FunctorId(index, retTypeId, TypeId<_recordType>::get(), _derivedType::getContainerId());
		}


		template<class _derivedType>
		template<class _recordType, class _retType, class ..._signature>
		inline const detail::FunctorId SetupMethod<_derivedType>::addFunctor(_retType(_recordType::* pFunctor)(_signature...) const,
										     enable_if_void<_retType> *_)
		{
			const auto functor = [=](const std::any& pTargetObj, _signature...params)->access::RStatus
			{
				_recordType* target = std::any_cast<_recordType*>(pTargetObj);
				((static_cast<const _recordType*>(target))->*pFunctor)(params...);
				return access::RStatus(Error::None);
			};

			const std::size_t& index = _derivedType::pushBack(functor);
			return detail::FunctorId(index, TypeId<_retType>::get(), TypeId<_recordType>::get(), _derivedType::getContainerId());
		}


		template<class _derivedType>
		template<class _recordType, class _retType, class ..._signature>
		inline const detail::FunctorId SetupMethod<_derivedType>::addFunctor(_retType(_recordType::* pFunctor)(_signature...) const,
										     enable_if_non_void<_retType> *_)
		{
			const std::size_t retTypeId = TypeId<_retType>::get();
			const std::size_t constRetTypeId = TypeId<const _retType>::get();
			const auto functor = [=](const std::any& pTargetObj, _signature...params)->access::RStatus
			{
				_recordType* target = std::any_cast<_recordType*>(pTargetObj);
				const TypeQ& qualifier = std::is_const<_retType>::value ? TypeQ::Const : TypeQ::Mute;
				const _retType& retObj = ((static_cast<const _recordType*>(target))->*pFunctor)(params...);
				return access::RStatus(std::make_any<_retType>(retObj), retTypeId, constRetTypeId, qualifier);
			};

			const std::size_t& index = _derivedType::pushBack(functor);
			return detail::FunctorId(index, retTypeId, TypeId<_recordType>::get(), _derivedType::getContainerId());
		}
	}
}