#pragma once

#include <cassert>
#include "TypeList.h"
#include "FunctorContainer.h"

namespace rtl {

	extern std::size_t g_containerId;

	namespace access 
	{
		template<class ..._signature>
		const std::size_t FunctorContainer<_signature...>::m_containerId = g_containerId++;


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
		inline std::unique_ptr<RObject> FunctorContainer<_signature...>::reflectCall(std::size_t pFunctorId, _params ..._args)
		{
			return m_functors.at(pFunctorId)(_args...);
		}


		template<class ..._signature>
		template<class ..._params>
		inline std::unique_ptr<RObject> FunctorContainer<_signature...>::reflectCall(const std::unique_ptr<RObject>& pTarget, std::size_t pFunctorId, _params ..._args)
		{
			return m_methodPtrs.at(pFunctorId)(pTarget, _args...);
		}


		template<class ..._signature>
		template<class _recordType>
		inline int FunctorContainer<_signature...>::addConstructor()
		{
			const auto& ctorType = TypeList<_recordType>::toString();
			const auto functor = [=](_signature...params)->std::unique_ptr<RObject>
			{
				_recordType* retObj = new _recordType(params...);
				return std::unique_ptr<RObject>(new ReturnObject<_recordType*>(ctorType, retObj));
			};
			m_functors.push_back(functor);
			return (m_functors.size() - 1);
		}


		template<class ..._signature>
		template<class _returnType>
		inline int FunctorContainer<_signature...>::addFunctor(_returnType(*pFunctor)(_signature...), enable_if_same<_returnType, void>* _)
		{
			const auto functor = [=](_signature...params)->std::unique_ptr<RObject>
			{
				(*pFunctor)(params...);
				return nullptr;
			};
			m_functors.push_back(functor);
			return (m_functors.size() - 1);
		}


		template<class ..._signature>
		template<class _returnType>
		inline int FunctorContainer<_signature...>::addFunctor(_returnType(*pFunctor)(_signature...), enable_if_notSame<_returnType, void>* _)
		{
			const auto& retTypeStr = TypeList<_returnType>::toString();
			const auto functor = [=](_signature...params)->std::unique_ptr<RObject>
			{
				const auto& retObj = (*pFunctor)(params...);
				return std::unique_ptr<RObject>(new ReturnObject<_returnType>(retTypeStr, retObj));
			};
			m_functors.push_back(functor);
			return (m_functors.size() - 1);
		}


		template<class ..._signature>
		template<class _recordType, class _returnType>
		inline int FunctorContainer<_signature...>::addFunctor(_returnType(_recordType::* pFunctor)(_signature...), enable_if_same<_returnType, void>* _)
		{
			const auto functor = [=](const std::unique_ptr<RObject>& pTargetObj, _signature...params)->std::unique_ptr<RObject>
			{
				auto targetObj = pTargetObj->get<_recordType*>();
				if (targetObj.has_value())
				{
					_recordType* target = targetObj.value();
					(target->*pFunctor)(params...);
				}
				else {
					assert(false && "Throw bad call exception");
				}
				return nullptr;
			};
			m_methodPtrs.push_back(functor);
			return (m_methodPtrs.size() - 1);
		}


		template<class ..._signature>
		template<class _recordType, class _returnType>
		inline int FunctorContainer<_signature...>::addFunctor(_returnType(_recordType::* pFunctor)(_signature...), enable_if_notSame<_returnType, void>* _)
		{
			const auto& retTypeStr = TypeList<_returnType>::toString();
			const auto functor = [=](const std::unique_ptr<RObject>& pTargetObj, _signature...params)->std::unique_ptr<RObject>
			{
				auto targetObj = pTargetObj->get<_recordType*>();
				if (targetObj.has_value())
				{
					_recordType* target = targetObj.value();
					const auto& retObj = (target->*pFunctor)(params...);
					return std::unique_ptr<RObject>(new ReturnObject<_returnType>(retTypeStr, retObj));
				}
				else {
					assert(false && "Throw bad call exception");
					return nullptr;
				}
			};
			m_methodPtrs.push_back(functor);
			return (m_methodPtrs.size() - 1);
		}
	}
}