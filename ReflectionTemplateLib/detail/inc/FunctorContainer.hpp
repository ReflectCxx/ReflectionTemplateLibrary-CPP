#pragma once

#include <cassert>

#include "Rany.h"
#include "TypeId.h"
#include "FunctorContainer.h"

namespace rtl {

	namespace detail 
	{
		extern std::size_t g_containerId;

		template<class ..._signature>
		const std::size_t FunctorContainer<_signature...>::m_containerId = ++g_containerId;


		template<class ..._signature>
		std::vector<typename FunctorContainer<_signature...>::FunctorType> FunctorContainer<_signature...>::m_functors;


		template<class ..._signature>
		std::vector<typename FunctorContainer<_signature...>::MethodPtrType> FunctorContainer<_signature...>::m_methodPtrs;


		template<class ..._signature>
		inline const std::size_t& FunctorContainer<_signature...>::getContainerId()
		{
			return m_containerId;
		}


		template<class ..._signature>
		template<class ..._params>
		inline access::Rany FunctorContainer<_signature...>::reflectCall(std::size_t pFunctorId, _params ..._args)
		{
			return m_functors.at(pFunctorId)(_args...);
		}


		template<class ..._signature>
		template<class ..._params>
		inline access::Rany FunctorContainer<_signature...>::reflectCall(const access::Rany& pTarget, std::size_t pFunctorId, _params ..._args)
		{
			return m_methodPtrs.at(pFunctorId)(pTarget, _args...);
		}


		template<class ..._signature>
		template<class _recordType>
		inline int FunctorContainer<_signature...>::addConstructor()
		{
			const auto functor = [=](_signature...params)->access::Rany
			{
				const auto& typeId = TypeId<_recordType*>::get();
				_recordType* retObj = new _recordType(params...);
				return access::Rany(std::make_any<_recordType*>(retObj), typeId);
			};
			m_functors.push_back(functor);
			return (m_functors.size() - 1);
		}


		template<class ..._signature>
		template<class _returnType>
		inline int FunctorContainer<_signature...>::addFunctor(_returnType(*pFunctor)(_signature...), enable_if_same<_returnType, void> *_)
		{
			const auto functor = [=](_signature...params)->access::Rany
			{
				(*pFunctor)(params...);
				return access::Rany();
			};
			m_functors.push_back(functor);
			return (m_functors.size() - 1);
		}


		template<class ..._signature>
		template<class _returnType>
		inline int FunctorContainer<_signature...>::addFunctor(_returnType(*pFunctor)(_signature...), enable_if_notSame<_returnType, void> *_)
		{
			const auto functor = [=](_signature...params)->access::Rany
			{
				const auto& retObj = (*pFunctor)(params...);
				const auto& typeId = TypeId<_returnType>::get();
				return access::Rany(std::make_any<_returnType>(retObj), typeId);
			};
			m_functors.push_back(functor);
			return (m_functors.size() - 1);
		}


		template<class ..._signature>
		template<class _recordType, class _returnType>
		inline int FunctorContainer<_signature...>::addFunctor(_returnType(_recordType::* pFunctor)(_signature...), enable_if_same<_returnType, void> *_)
		{
			const auto functor = [=](const access::Rany& pTargetObj, _signature...params)->access::Rany
			{
				if (pTargetObj.get().has_value() && pTargetObj.isOfType<_recordType*>())
				{
					_recordType* target = std::any_cast<_recordType*>(pTargetObj.get());
					if (target != nullptr) 
					{
						(target->*pFunctor)(params...);
						return access::Rany();
					}
					assert(false && "Throw call on bad target exception");
				}
				assert(false && "Throw call on bad target exception");
				return access::Rany();
			};
			m_methodPtrs.push_back(functor);
			return (m_methodPtrs.size() - 1);
		}


		template<class ..._signature>
		template<class _recordType, class _returnType>
		inline int FunctorContainer<_signature...>::addFunctor(_returnType(_recordType::* pFunctor)(_signature...), enable_if_notSame<_returnType, void> *_)
		{
			const auto functor = [=](const access::Rany& pTargetObj, _signature...params)->access::Rany
			{
				if (pTargetObj.get().has_value() && pTargetObj.isOfType<_recordType*>())
				{
					_recordType* target = std::any_cast<_recordType*>(pTargetObj.get());
					if (target != nullptr) 
					{
						const auto& typeId = TypeId<_returnType>::get();
						const auto& retObj = (target->*pFunctor)(params...);
						return access::Rany(std::make_any<_returnType>(retObj), typeId);
					}
					assert(false && "Throw call on bad target exception");
				}
				assert(false && "Throw call on bad target exception");
				return access::Rany();
			};
			m_methodPtrs.push_back(functor);
			return (m_methodPtrs.size() - 1);
		}
	}
}