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
			return std::stoull(std::to_string(pContainerId) + std::to_string(pArgsCount) +
					   std::to_string(pIndex) + std::to_string(TypeId<_recordType>::get()));
		}


		template<class _derivedType>
		template<class _recordType>
		inline const std::function<void(std::any&, std::size_t&)> SetupConstructor<_derivedType>::getConstConverter()
		{
			return [](std::any& pTarget, std::size_t& pTypeId)->void
			{
				_recordType* object = std::any_cast<_recordType*>(pTarget);
				pTarget.reset();
				pTarget.emplace<const _recordType*>(object);
				pTypeId = TypeId<const _recordType*>::get();
			};
		}


		template<class _derivedType>
		template<class _recordType>
		inline const std::function<void(const std::any&, const TypeQ&)> SetupConstructor<_derivedType>::getDestructor()
		{
			return [](const std::any& pTarget, const TypeQ& pQualifier)->void
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
			};
		}


		template<class _derivedType>
		template<class _recordType, class ..._signature>
		inline const detail::FunctorId SetupConstructor<_derivedType>::pushBack()
		{
			const auto functor = [=](_signature...params)->access::RStatus
			{
				const auto& typeId = TypeId<_recordType*>::get();
				_recordType* retObj = new _recordType(params...);
				return access::RStatus(true, std::make_any<_recordType*>(retObj), typeId, TypeQ::Mute,
						       getDestructor<_recordType>(), getConstConverter<_recordType>());
			};

			auto& ctorFunctors = _derivedType::getCtorFunctors();
			const std::size_t& index = ctorFunctors.size();
			const std::size_t& argsCount = sizeof...(_signature);
			const std::size_t& hashCode = getHashCode<_recordType>(_derivedType::getContainerId(), index, argsCount);
			ctorFunctors.push_back(std::make_pair(hashCode, functor));
			return detail::FunctorId(index, hashCode, _derivedType::getContainerId(), argsCount);
		}
	}
}