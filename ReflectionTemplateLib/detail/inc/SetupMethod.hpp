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
		template<class _recordType, class _retType>
		inline const std::size_t SetupMethod<_derivedType>::getHashCode(const std::size_t pContainerId, const std::size_t pIndex,
										const std::size_t pArgsCount)
		{
			return std::stoull(std::to_string(pContainerId) + std::to_string(pIndex) +
					   std::to_string(TypeId<_retType>::get()) + std::to_string(TypeId<_recordType>::get()) +
					   std::to_string(pArgsCount));
		}


		template<class _derivedType>
		template<class _recordType, class _retType, class ..._signature>
		inline const detail::FunctorId SetupMethod<_derivedType>::pushBack(_retType(_recordType::* pFunctor)(_signature...),
										   enable_if_void<_retType> *_)
		{
			const std::size_t objTypeId = TypeId<_recordType*>::get();
			const auto functor = [=](const access::Instance& pTargetObj, _signature...params)->access::RStatus
			{
				if (!pTargetObj.get().has_value()) {
					assert(false && "Throw call on bad target exception");
					return access::RStatus(false);
				}

				if (pTargetObj.getTypeId() == objTypeId && !pTargetObj.isConst())
				{
					_recordType* target = std::any_cast<_recordType*>(pTargetObj.get());
					if (target != nullptr)
					{
						(target->*pFunctor)(params...);
						return access::RStatus(true);
					}
					assert(false && "Throw call on bad target exception");
				}
				return access::RStatus(false);
			};

			auto& methodFunctors = _derivedType::getMethodFunctors();
			const std::size_t& index = methodFunctors.size();
			const std::size_t& argsCount = sizeof...(_signature);
			const std::size_t& hashCode = getHashCode<_recordType, _retType>(_derivedType::getContainerId(), index, argsCount);
			methodFunctors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId(), argsCount, FunctorType::Method);
		}


		template<class _derivedType>
		template<class _recordType, class _retType, class ..._signature>
		inline const detail::FunctorId SetupMethod<_derivedType>::pushBack(_retType(_recordType::* pFunctor)(_signature...),
										   enable_if_non_void<_retType> *_)
		{
			const std::size_t retTypeId = TypeId<_retType>::get();
			const std::size_t constRetTypeId = TypeId<const _retType>::get();
			const std::size_t objTypeId = TypeId<_recordType*>::get();
			const auto functor = [=](const access::Instance& pTargetObj, _signature...params)->access::RStatus
			{
				if (!pTargetObj.get().has_value()) {
					assert(false && "Throw call on bad target exception");
					return access::RStatus(false);
				}

				if (pTargetObj.getTypeId() == objTypeId && !pTargetObj.isConst())
				{
					_recordType* target = std::any_cast<_recordType*>(pTargetObj.get());
					if (target != nullptr)
					{
						const _retType& retObj = (target->*pFunctor)(params...);
						const TypeQ& qualifier = std::is_const<_retType>::value ? TypeQ::Const : TypeQ::Mute;
						return access::RStatus(true, std::make_any<_retType>(retObj), retTypeId, constRetTypeId, qualifier);
					}
					assert(false && "Throw call on bad target exception");
				}
				return access::RStatus(false);
			};

			auto& methodFunctors = _derivedType::getMethodFunctors();
			const std::size_t& index = methodFunctors.size();
			const std::size_t& argsCount = sizeof...(_signature);
			const std::size_t& hashCode = getHashCode<_recordType, _retType>(_derivedType::getContainerId(), index, argsCount);
			methodFunctors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId(), argsCount, FunctorType::Method);
		}


		template<class _derivedType>
		template<class _recordType, class _retType, class ..._signature>
		inline const detail::FunctorId SetupMethod<_derivedType>::pushBack(_retType(_recordType::* pFunctor)(_signature...) const,
										   enable_if_void<_retType> *_)
		{
			const std::size_t objTypeId = TypeId<_recordType*>::get();
			const auto functor = [=](const access::Instance& pTargetObj, _signature...params)->access::RStatus
			{
				if (!pTargetObj.get().has_value()) {
					assert(false && "Throw call on bad target exception");
					return access::RStatus(false);
				}

				if (pTargetObj.getTypeId() == objTypeId)
				{
					_recordType* target = std::any_cast<_recordType*>(pTargetObj.get());
					if (target != nullptr)
					{
						((static_cast<const _recordType*>(target))->*pFunctor)(params...); 
						return access::RStatus(true);
					}
					assert(false && "Throw call on bad target exception");
				}
				return access::RStatus(false);
			};

			auto& methodFunctors = _derivedType::getMethodFunctors();
			const std::size_t& index = methodFunctors.size();
			const std::size_t& argsCount = sizeof...(_signature);
			const std::size_t& hashCode = getHashCode<_recordType, _retType>(_derivedType::getContainerId(), index, argsCount);
			methodFunctors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId(), argsCount, FunctorType::Method);
		}


		template<class _derivedType>
		template<class _recordType, class _retType, class ..._signature>
		inline const detail::FunctorId SetupMethod<_derivedType>::pushBack(_retType(_recordType::* pFunctor)(_signature...) const,
										   enable_if_non_void<_retType> *_)
		{
			const std::size_t retTypeId = TypeId<_retType>::get();
			const std::size_t constRetTypeId = TypeId<const _retType>::get();
			const std::size_t objTypeId = TypeId<_recordType*>::get();
			const auto functor = [=](const access::Instance& pTargetObj, _signature...params)->access::RStatus
			{
				if (!pTargetObj.get().has_value()) {
					assert(false && "Throw call on bad target exception");
					return access::RStatus(false);
				}

				if (pTargetObj.getTypeId() == objTypeId)
				{
					_recordType* target = std::any_cast<_recordType*>(pTargetObj.get());
					if (target != nullptr)
					{
						const TypeQ& qualifier = std::is_const<_retType>::value ? TypeQ::Const : TypeQ::Mute;
						const _retType& retObj = ((static_cast<const _recordType*>(target))->*pFunctor)(params...);
						return access::RStatus(true, std::make_any<_retType>(retObj), retTypeId, constRetTypeId, qualifier);
					}
					assert(false && "Throw call on bad target exception");
				}
				return access::RStatus(false);
			};

			auto& methodFunctors = _derivedType::getMethodFunctors();
			const std::size_t& index = methodFunctors.size();
			const std::size_t& argsCount = sizeof...(_signature);
			const std::size_t& hashCode = getHashCode<_recordType, _retType>(_derivedType::getContainerId(), index, argsCount);
			methodFunctors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId(), argsCount, FunctorType::Method);
		}
	}
}