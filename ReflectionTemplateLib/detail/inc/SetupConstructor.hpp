#pragma once
#include <map>

#include "RStatus.h"
#include "SetupConstructor.h"

namespace rtl 
{
	namespace detail
	{
		template<class _derivedType>
		template<class _recordType>
		inline const detail::FunctorId SetupConstructor<_derivedType>::addDestructor()
		{
			static std::size_t dctorIndex = -1;
			const auto& updateIndex = [&](const std::size_t& pIndex) {
				dctorIndex = pIndex;
			};
			const auto& getIndex = [&]()->const std::size_t {
				return dctorIndex;
			};

			const auto& functor = [](const std::any& pTarget)->access::RStatus
			{
				_recordType* object = std::any_cast<_recordType*>(pTarget);
				delete object;
				return access::RStatus(Error::None);
			};

			const std::size_t& index = _derivedType::pushBack(functor, getIndex, updateIndex);
			return detail::FunctorId(index, TypeId<>::None, TypeId<_recordType>::get(), _derivedType::getContainerId(), 
						 (std::string("~") + _derivedType::template getSignatureStr<_recordType>(true)));
		}


		template<class _derivedType>
		template<class _recordType, class ..._signature>
		inline const detail::FunctorId SetupConstructor<_derivedType>::addConstructor()
		{
			const auto& recordId = TypeId<_recordType>::get();
			const auto& containerId = _derivedType::getContainerId();
			const auto& hashKey = std::stoull(std::to_string(containerId) + std::to_string(recordId));

			static std::map<std::size_t, std::size_t> ctorSet;
			const auto& updateIndex = [&](const std::size_t& pIndex) {
				ctorSet.insert(std::make_pair(hashKey, pIndex));
			};
			const auto& getIndex = [&]()->const std::size_t {
				const auto& itr = ctorSet.find(hashKey);
				return (itr != ctorSet.end() ? itr->second : -1);
			};

			const auto& functor = [=](_signature...params)->access::RStatus
			{
				_recordType* retObj = new _recordType(params...);
				return access::RStatus(std::make_any<_recordType*>(retObj), recordId, TypeQ::Mute);
			};

			const std::size_t& index = _derivedType::pushBack(functor, getIndex, updateIndex);
			return detail::FunctorId(index, TypeId<_recordType>::get(), recordId, containerId,
						 _derivedType::template getSignatureStr<_recordType>(true));
		}


		template<class _derivedType>
		template<class _recordType>
		inline const detail::FunctorId SetupConstructor<_derivedType>::addCopyConstructor()
		{
			static std::size_t copyCtorIndex = -1;
			const auto& updateIndex = [&](const std::size_t& pIndex) {
				copyCtorIndex = pIndex;
			};
			const auto& getIndex = [&]()->const std::size_t {
				return copyCtorIndex;
			};

			const auto& recordId = TypeId<_recordType>::get();
			const auto& functor = [=](const std::any& pOther)->access::RStatus
			{
				_recordType* srcObj = std::any_cast<_recordType*>(pOther);
				_recordType* retObj = new _recordType(*srcObj);
				return access::RStatus(std::make_any<_recordType*>(retObj), recordId, TypeQ::Mute);
			};

			const std::size_t& index = _derivedType::pushBack(functor, getIndex, updateIndex);
			return detail::FunctorId(index, TypeId<_recordType>::get(), recordId, _derivedType::getContainerId(),
						 _derivedType::template getSignatureStr<_recordType>(true));
		}


		template<class _derivedType>
		template<class _recordType>
		inline const detail::FunctorId SetupConstructor<_derivedType>::addConstCopyConstructor()
		{
			static std::size_t constCopyCtorIndex = -1;
			const auto& updateIndex = [&](const std::size_t& pIndex) {
				constCopyCtorIndex = pIndex;
			};
			const auto& getIndex = [&]()->const std::size_t {
				return constCopyCtorIndex;
			};

			const auto& recordId = TypeId<_recordType>::get();
			const auto& functor = [=](const std::any& pOther)->access::RStatus
			{
				const _recordType* srcObj = std::any_cast<_recordType*>(pOther);
				_recordType* retObj = new _recordType(*srcObj);
				return access::RStatus(std::make_any<_recordType*>(retObj), recordId, TypeQ::Mute);
			};

			const std::size_t& index = _derivedType::pushBack(functor, getIndex, updateIndex);
			return detail::FunctorId(index, TypeId<_recordType>::get(), recordId, _derivedType::getContainerId(),
						 _derivedType::template getSignatureStr<_recordType>(true));
		}
	}
}