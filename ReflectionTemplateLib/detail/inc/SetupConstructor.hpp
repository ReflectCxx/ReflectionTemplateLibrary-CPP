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
			return std::stoull(std::to_string(pContainerId) +
					   std::to_string(pIndex) +
					   std::to_string(TypeId<_recordType>::get()) +
					   std::to_string(pArgsCount));
		}


		template<class _derivedType>
		template<class _recordType>
		inline const detail::FunctorId SetupConstructor<_derivedType>::pushBackDCtor(int& pDctorIndex)
		{
			if (pDctorIndex == -1) {
				const auto functor = [](const std::any& pTarget)->access::RStatus
				{
					_recordType* object = std::any_cast<_recordType*>(pTarget);
					delete object;
					return access::RStatus(Error::None);
				};
				auto& ctorFunctors = _derivedType::getContainer();
				pDctorIndex = ctorFunctors.size();
				const std::size_t& hashCode = getHashCode<_recordType>(_derivedType::getContainerId(), pDctorIndex, 1);
				ctorFunctors.push_back(std::make_pair(hashCode, functor));
				return detail::FunctorId(pDctorIndex, hashCode, _derivedType::getContainerId(), 1, FunctorType::DCtor);
			}
			else 
			{
				const std::size_t& hashCode = getHashCode<_recordType>(_derivedType::getContainerId(), pDctorIndex, 1);
				return detail::FunctorId(pDctorIndex, hashCode, _derivedType::getContainerId(), 1, FunctorType::DCtor);
			}
		}


		template<class _derivedType>
		template<class _recordType, class ..._signature>
		inline const detail::FunctorId SetupConstructor<_derivedType>::pushBackCtor()
		{
			const auto& typeId = TypeId<_recordType>::get();
			const auto functor = [=](_signature...params)->access::RStatus
			{
				_recordType* retObj = new _recordType(params...);
				return access::RStatus(std::make_any<_recordType*>(retObj), typeId, TypeQ::Mute);
			};

			auto& ctorFunctors = _derivedType::getContainer();
			const std::size_t& index = ctorFunctors.size();
			const std::size_t& argsCount = sizeof...(_signature);
			const std::size_t& hashCode = getHashCode<_recordType>(_derivedType::getContainerId(), index, argsCount);
			ctorFunctors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId(), argsCount, FunctorType::Ctor);
		}


		template<class _derivedType>
		template<class _recordType>
		inline const detail::FunctorId SetupConstructor<_derivedType>::pushBackCopyCtor()
		{
			const auto& typeId = TypeId<_recordType>::get();
			const auto functor = [=](const std::any& pOther)->access::RStatus
			{
				_recordType* srcObj = std::any_cast<_recordType*>(pOther);
				_recordType* retObj = new _recordType(*srcObj);
				return access::RStatus(std::make_any<_recordType*>(retObj), typeId, TypeQ::Mute);
			};

			auto& ctorFunctors = _derivedType::getContainer();
			const std::size_t& index = ctorFunctors.size();
			const std::size_t& hashCode = getHashCode<_recordType>(_derivedType::getContainerId(), index, 1);
			ctorFunctors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId(), 1, FunctorType::CopyCtor);
		}


		template<class _derivedType>
		template<class _recordType>
		inline const detail::FunctorId SetupConstructor<_derivedType>::pushBackCopyCtorConst()
		{
			const auto& typeId = TypeId<_recordType>::get();
			const auto functor = [=](const std::any& pOther)->access::RStatus
			{
				const _recordType* srcObj = std::any_cast<_recordType*>(pOther);
				_recordType* retObj = new _recordType(*srcObj);
				return access::RStatus(std::make_any<_recordType*>(retObj), typeId, TypeQ::Mute);
			};

			auto& ctorFunctors = _derivedType::getContainer();
			const std::size_t& index = ctorFunctors.size();
			const std::size_t& hashCode = getHashCode<_recordType>(_derivedType::getContainerId(), index, 1);
			ctorFunctors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId(), 1, FunctorType::CopyCtorConst);
		}
	}
}