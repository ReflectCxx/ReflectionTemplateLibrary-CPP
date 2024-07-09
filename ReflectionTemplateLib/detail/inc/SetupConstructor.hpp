#pragma once

#include <cassert>

#include "RStatus.h"
#include "SetupConstructor.h"

namespace rtl 
{
	namespace detail
	{
		template<class _derivedType>
		template<class _recordType>
		inline const std::size_t SetupConstructor<_derivedType>::getHashCode(const std::size_t pContainerId, const std::size_t pIndex, 
										     const std::size_t pArgsCount)
		{
			return std::stoull(std::to_string(pContainerId) + std::to_string(pIndex) +
					   std::to_string(TypeId<_recordType>::get()) + std::to_string(pArgsCount));
		}


		template<class _derivedType>
		template<class _recordType>
		inline const detail::FunctorId SetupConstructor<_derivedType>::pushBackDCtor()
		{
			const auto functor = [](const std::any& pTarget, const TypeQ& pQualifier)->access::RStatus
			{
				if (pQualifier == TypeQ::Const) {
					const _recordType* object = std::any_cast<const _recordType*>(pTarget);
					delete object;
				}
				else if (pQualifier == TypeQ::Mute) {
					_recordType* object = std::any_cast<_recordType*>(pTarget);
					delete object;
				}
				else {
					assert(false && "deleting bad target object.");
				}
				return access::RStatus(true);
			};

			auto& ctorFunctors = _derivedType::getFunctors();
			const std::size_t& index = ctorFunctors.size();
			const std::size_t& argsCount = 2;
			const std::size_t& hashCode = getHashCode<_recordType>(_derivedType::getContainerId(), index, argsCount);
			ctorFunctors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId(), argsCount, FunctorType::DCtor);
		}


		template<class _derivedType>
		template<class _recordType>
		inline const detail::FunctorId SetupConstructor<_derivedType>::pushBackConstConverter()
		{
			const auto functor = [](std::any pTarget)->access::RStatus
			{
				_recordType* object = std::any_cast<_recordType*>(pTarget);
				const std::size_t& typeId = TypeId<const _recordType*>::get();
				return access::RStatus(true, std::make_any<const _recordType*>(object), typeId, TypeQ::None);
			};

			auto& ctorFunctors = _derivedType::getFunctors();
			const std::size_t& index = ctorFunctors.size();
			const std::size_t& argsCount = 2;
			const std::size_t& hashCode = getHashCode<_recordType>(_derivedType::getContainerId(), index, argsCount);
			ctorFunctors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId(), argsCount, FunctorType::ConstConverter);
		}


		template<class _derivedType>
		template<class _recordType, class ..._signature>
		inline const detail::FunctorId SetupConstructor<_derivedType>::pushBackCtor()
		{
			const auto functor = [=](_signature...params)->access::RStatus
			{
				const auto& typeId = TypeId<_recordType*>::get();
				_recordType* retObj = new _recordType(params...);
				return access::RStatus(true, std::make_any<_recordType*>(retObj), typeId, TypeQ::Mute);
			};

			auto& ctorFunctors = _derivedType::getFunctors();
			const std::size_t& index = ctorFunctors.size();
			const std::size_t& argsCount = sizeof...(_signature);
			const std::size_t& hashCode = getHashCode<_recordType>(_derivedType::getContainerId(), index, argsCount);
			ctorFunctors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId(), argsCount, FunctorType::Ctor);
		}
	}
}