
#include <cassert>

#include "RStatus.h"
#include "SetupMethod.h"

namespace rtl 
{
	namespace detail
	{
		template<class _derivedType>
		template<class _recordType, class _returnType, class ..._signature>
		inline int SetupMethod<_derivedType>::addMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...), enable_if_same<_returnType, void> *_)
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
			methodFunctors.push_back(functor);
			return (methodFunctors.size() - 1);
		}


		template<class _derivedType>
		template<class _recordType, class _returnType, class ..._signature>
		inline int SetupMethod<_derivedType>::addMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...), enable_if_notSame<_returnType, void> *_)
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
			methodFunctors.push_back(functor);
			return (methodFunctors.size() - 1);
		}

		template<class _derivedType>
		template<class _recordType, class _returnType, class ..._signature>
		inline int SetupMethod<_derivedType>::addMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...) const, enable_if_same<_returnType, void> *_)
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
			methodFunctors.push_back(functor);
			return (methodFunctors.size() - 1);
		}


		template<class _derivedType>
		template<class _recordType, class _returnType, class ..._signature>
		inline int SetupMethod<_derivedType>::addMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...) const, enable_if_notSame<_returnType, void> *_)
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
			methodFunctors.push_back(functor);
			return (methodFunctors.size() - 1);
		}
	}
}