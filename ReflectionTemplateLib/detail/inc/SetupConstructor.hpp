#pragma once

#include "RStatus.h"
#include "SetupConstructor.h"

namespace rtl 
{
	namespace detail
	{
		template<class _derivedType>
		template<class _recordType>
		inline const std::size_t SetupConstructor<_derivedType>::getHashCode(const std::size_t pContainerId)
		{
			return std::stoull(std::to_string(TypeId<_recordType>::get()) + std::to_string(pContainerId));
		}


		template<class _derivedType>
		template<class _recordType, class ..._signature>
		inline const access::FunctorId SetupConstructor<_derivedType>::pushBack()
		{
			const auto functor = [=](_signature...params)->access::RStatus
			{
				const auto& typeId = TypeId<_recordType*>::get();
				_recordType* retObj = new _recordType(params...);
				std::function< void(const std::any&) > destructor = [](const std::any& pTarget)->void {
					_recordType* object = std::any_cast<_recordType*>(pTarget);
					delete object;
				};
				return access::RStatus(true, std::make_any<_recordType*>(retObj), typeId, TypeQ::Vol, destructor);
			};

			auto& ctorFunctors = _derivedType::getCtorFunctors();
			auto hashCode = getHashCode<_recordType>(_derivedType::getContainerId());
			ctorFunctors.push_back(std::make_pair(hashCode, functor));
			return access::FunctorId(ctorFunctors.size() - 1, hashCode, _derivedType::getContainerId());
		}
	}
}