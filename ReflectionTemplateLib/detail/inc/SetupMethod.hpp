#pragma once

#include <cassert>

#include "RStatus.h"
#include "SetupMethod.h"

namespace rtl 
{
	namespace detail
	{
		template<class _derivedType>
		template<class _recordType, class _returnType>
		inline const std::size_t SetupMethod<_derivedType>::getHashCode(const std::size_t pContainerId, const std::size_t pIndex)
		{
			return std::stoull(std::to_string(TypeId<_recordType>::get()) +
					   std::to_string(TypeId<_returnType>::get()) +
					   std::to_string(pContainerId) + 
					   std::to_string(pIndex));
		}


		template<class _derivedType>
		template<class _recordType, class _returnType, class ..._signature>
		inline const detail::FunctorId SetupMethod<_derivedType>::pushBack(_returnType(_recordType::* pFunctor)(_signature...),
										   enable_if_same<_returnType, void> *_)
		{
			const auto functor = [=](const access::UniqueAny& pTargetObj, _signature...params)->access::RStatus
			{
				if (pTargetObj.get().has_value() && pTargetObj.isOfType<_recordType*>())
				{
					_recordType* target = std::any_cast<_recordType*>(pTargetObj.get());
					if (target != nullptr)
					{
						(target->*pFunctor)(params...);
						return access::RStatus(true);
					}
					assert(false && "Throw call on bad target exception");
				}
				assert(false && "Throw call on bad target exception");
				return access::RStatus(false);
			};

			auto& methodFunctors = _derivedType::getMethodFunctors();
			const std::size_t& index = methodFunctors.size();
			auto hashCode = getHashCode<_recordType, _returnType>(_derivedType::getContainerId(), index);
			methodFunctors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId());
		}


		template<class _derivedType>
		template<class _recordType, class _returnType, class ..._signature>
		inline const detail::FunctorId SetupMethod<_derivedType>::pushBack(_returnType(_recordType::* pFunctor)(_signature...),
										   enable_if_notSame<_returnType, void> *_)
		{
			const auto functor = [=](const access::UniqueAny& pTargetObj, _signature...params)->access::RStatus
			{
				if (pTargetObj.get().has_value() && pTargetObj.isOfType<_recordType*>())
				{
					_recordType* target = std::any_cast<_recordType*>(pTargetObj.get());
					if (target != nullptr)
					{
						const auto& typeId = TypeId<_returnType>::get();
						const _returnType& retObj = (target->*pFunctor)(params...);
						const TypeQ& qualifier = std::is_const<_returnType>::value ? TypeQ::Const : TypeQ::Vol;
						return access::RStatus(true, std::make_any<_returnType>(retObj), typeId, qualifier);
					}
					assert(false && "Throw call on bad target exception");
				}
				assert(false && "Throw call on bad target exception");
				return access::RStatus(false);
			};

			auto& methodFunctors = _derivedType::getMethodFunctors();
			const std::size_t& index = methodFunctors.size();
			auto hashCode = getHashCode<_recordType, _returnType>(_derivedType::getContainerId(), index);
			methodFunctors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId());
		}


		template<class _derivedType>
		template<class _recordType, class _returnType, class ..._signature>
		inline const detail::FunctorId SetupMethod<_derivedType>::pushBack(_returnType(_recordType::* pFunctor)(_signature...) const,
										   enable_if_same<_returnType, void> *_)
		{
			const auto functor = [=](const access::UniqueAny& pTargetObj, _signature...params)->access::RStatus
			{
				if (pTargetObj.get().has_value())
				{
					if (pTargetObj.isConst() && pTargetObj.isOfType<const _recordType*>()) {
						const _recordType* target = std::any_cast<const _recordType*>(pTargetObj.get());
						if (target != nullptr)
						{
							(target->*pFunctor)(params...);
							return access::RStatus(true);
						}
					}
					else if (pTargetObj.isOfType<_recordType*>()) {
						_recordType* target = std::any_cast<_recordType*>(pTargetObj.get());
						if (target != nullptr)
						{
							(target->*pFunctor)(params...);
							return access::RStatus(true);
						}
					}
					assert(false && "Throw call on bad target exception");
				}
				assert(false && "Throw call on bad target exception");
				return access::RStatus(false);
			};

			auto& methodFunctors = _derivedType::getMethodFunctors();
			const std::size_t& index = methodFunctors.size();
			auto hashCode = getHashCode<_recordType, _returnType>(_derivedType::getContainerId(), index);
			methodFunctors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId());
		}


		template<class _derivedType>
		template<class _recordType, class _returnType, class ..._signature>
		inline const detail::FunctorId SetupMethod<_derivedType>::pushBack(_returnType(_recordType::* pFunctor)(_signature...) const,
										   enable_if_notSame<_returnType, void> *_)
		{
			const auto functor = [=](const access::UniqueAny& pTargetObj, _signature...params)->access::RStatus
			{
				if (pTargetObj.get().has_value() && pTargetObj.isOfType<_recordType*>())
				{
					_recordType* target = std::any_cast<_recordType*>(pTargetObj.get());
					if (target != nullptr)
					{
						const auto& typeId = TypeId<_returnType>::get();
						const _returnType& retObj = (target->*pFunctor)(params...);
						return access::RStatus(true, std::make_any<_returnType>(retObj), typeId);
					}
					assert(false && "Throw call on bad target exception");
				}
				assert(false && "Throw call on bad target exception");
				return access::RStatus(false);
			};

			auto& methodFunctors = _derivedType::getMethodFunctors();
			const std::size_t& index = methodFunctors.size();
			auto hashCode = getHashCode<_recordType, _returnType>(_derivedType::getContainerId(), index);
			methodFunctors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId());
		}
	}
}