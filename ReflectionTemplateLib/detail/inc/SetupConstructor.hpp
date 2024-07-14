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
		inline const detail::FunctorId SetupConstructor<_derivedType>::addDestructor(int& pDctorIndex)
		{
			if (pDctorIndex == -1) {
				const auto functor = [](const std::any& pTarget)->access::RStatus
				{
					_recordType* object = std::any_cast<_recordType*>(pTarget);
					delete object;
					return access::RStatus(Error::None);
				};
				pDctorIndex = _derivedType::pushBack(functor);
			}
			return detail::FunctorId(pDctorIndex, TypeId<>::None, TypeId<_recordType>::get(), _derivedType::getContainerId());
		}


		template<class _derivedType>
		template<class _recordType, class ..._signature>
		inline const detail::FunctorId SetupConstructor<_derivedType>::addConstructor()
		{
			const auto& typeId = TypeId<_recordType>::get();
			const auto functor = [=](_signature...params)->access::RStatus
			{
				_recordType* retObj = new _recordType(params...);
				return access::RStatus(std::make_any<_recordType*>(retObj), typeId, TypeQ::Mute);
			};

			const std::size_t& index = _derivedType::pushBack(functor);
			return detail::FunctorId(index, TypeId<_recordType>::get(), TypeId<_recordType>::get(), _derivedType::getContainerId());
		}


		template<class _derivedType>
		template<class _recordType>
		inline const detail::FunctorId SetupConstructor<_derivedType>::addCopyConstructor()
		{
			const auto& typeId = TypeId<_recordType>::get();
			const auto functor = [=](const std::any& pOther)->access::RStatus
			{
				_recordType* srcObj = std::any_cast<_recordType*>(pOther);
				_recordType* retObj = new _recordType(*srcObj);
				return access::RStatus(std::make_any<_recordType*>(retObj), typeId, TypeQ::Mute);
			};

			const std::size_t& index = _derivedType::pushBack(functor);
			return detail::FunctorId(index, TypeId<_recordType>::get(), TypeId<_recordType>::get(), _derivedType::getContainerId());
		}


		template<class _derivedType>
		template<class _recordType>
		inline const detail::FunctorId SetupConstructor<_derivedType>::addConstCopyConstructor()
		{
			const auto& typeId = TypeId<_recordType>::get();
			const auto functor = [=](const std::any& pOther)->access::RStatus
			{
				const _recordType* srcObj = std::any_cast<_recordType*>(pOther);
				_recordType* retObj = new _recordType(*srcObj);
				return access::RStatus(std::make_any<_recordType*>(retObj), typeId, TypeQ::Mute);
			};

			const std::size_t& index = _derivedType::pushBack(functor);
			return detail::FunctorId(index, TypeId<_recordType>::get(), TypeId<_recordType>::get(), _derivedType::getContainerId());
		}
	}
}