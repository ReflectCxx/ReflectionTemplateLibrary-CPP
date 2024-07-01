#pragma once

#include <cassert>

#include "RStatus.h"
#include "TypeId.h"
#include "FunctorContainer.h"

namespace rtl {

	namespace detail 
	{
		extern std::size_t g_signIdCounter;

		template<class ..._signature>
		const std::size_t FunctorContainer<_signature...>::m_containerId = g_signIdCounter++;

		template<class ..._signature>
		std::vector<typename FunctorContainer<_signature...>::FunctorType> FunctorContainer<_signature...>::m_functors;

		template<class ..._signature>
		std::vector<typename FunctorContainer<_signature...>::CtorFunctorType> FunctorContainer<_signature...>::m_ctorPtrs;

		template<class ..._signature>
		std::vector<typename FunctorContainer<_signature...>::MethodPtrType> FunctorContainer<_signature...>::m_methodPtrs;


		template<class ..._signature>
		inline const std::size_t& FunctorContainer<_signature...>::getContainerId()
		{
			return m_containerId;
		}


		template<class ..._signature>
		template<class ..._params>
		inline access::RStatus FunctorContainer<_signature...>::reflectFunctionCall(std::size_t pFunctorId, _params ..._args)
		{
			return m_functors.at(pFunctorId)(_args...);
		}

		template<class ..._signature>
		template<class ..._params>
		inline access::RStatus FunctorContainer<_signature...>::reflectConstructorCall(std::size_t pFunctorId, _params ..._args)
		{
			return m_ctorPtrs.at(pFunctorId)(_args...);
		}


		template<class ..._signature>
		template<class ..._params>
		inline access::RStatus FunctorContainer<_signature...>::reflectMethodCall(const access::UniqueAny& pTarget, std::size_t pFunctorId, _params ..._args)
		{
			return m_methodPtrs.at(pFunctorId)(pTarget, _args...);
		}


		template<class ..._signature>
		template<class _recordType>
		inline int FunctorContainer<_signature...>::addConstructor()
		{
			const auto functor = [=](_signature...params)->access::RStatus
			{
				const auto& typeId = TypeId<_recordType*>::get();
				_recordType* retObj = new _recordType(params...);
				std::function<void(const std::any&)> destructor = [](const std::any& pTarget)->void {
					_recordType* object = std::any_cast<_recordType*>(pTarget);
					delete object;
				};
				return access::RStatus(true, std::make_any<_recordType*>(retObj), typeId, destructor);
			};
			m_ctorPtrs.push_back(functor);
			return (m_ctorPtrs.size() - 1);
		}


		template<class ..._signature>
		template<class _returnType>
		inline int FunctorContainer<_signature...>::addFunctor(_returnType(*pFunctor)(_signature...), enable_if_same<_returnType, void> *_)
		{
			const auto functor = [=](_signature...params)->access::RStatus
			{
				(*pFunctor)(params...);
				return access::RStatus(true);
			};
			m_functors.push_back(functor);
			return (m_functors.size() - 1);
		}


		template<class ..._signature>
		template<class _returnType>
		inline int FunctorContainer<_signature...>::addFunctor(_returnType(*pFunctor)(_signature...), enable_if_notSame<_returnType, void> *_)
		{
			const auto functor = [=](_signature...params)->access::RStatus
			{
				const auto& typeId = TypeId<_returnType>::get();
				const _returnType& retObj = (*pFunctor)(params...);
				return access::RStatus(true, std::make_any<_returnType>(retObj), typeId);
			};
			m_functors.push_back(functor);
			return (m_functors.size() - 1);
		}


		template<class ..._signature>
		template<class _recordType, class _returnType>
		inline int FunctorContainer<_signature...>::addFunctor(_returnType(_recordType::* pFunctor)(_signature...), enable_if_same<_returnType, void> *_)
		{
			const auto functor = [=](const access::UniqueAny& pTargetObj, _signature...params)->access::RStatus
			{
				if (pTargetObj.getReturn().has_value() && pTargetObj.isOfType<_recordType*>())
				{
					_recordType* target = std::any_cast<_recordType*>(pTargetObj.getReturn());
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
			m_methodPtrs.push_back(functor);
			return (m_methodPtrs.size() - 1);
		}


		template<class ..._signature>
		template<class _recordType, class _returnType>
		inline int FunctorContainer<_signature...>::addFunctor(_returnType(_recordType::* pFunctor)(_signature...), enable_if_notSame<_returnType, void> *_)
		{
			const auto functor = [=](const access::UniqueAny& pTargetObj, _signature...params)->access::RStatus
			{
				if (pTargetObj.getReturn().has_value() && pTargetObj.isOfType<_recordType*>())
				{
					_recordType* target = std::any_cast<_recordType*>(pTargetObj.getReturn());
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
			m_methodPtrs.push_back(functor);
			return (m_methodPtrs.size() - 1);
		}
	}
}