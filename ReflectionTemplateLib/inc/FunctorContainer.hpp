#pragma once

#include <cassert>

#include "FunctorContainer.h"

namespace rtl {

	extern std::size_t g_containerId;


	template<class ..._signature>
	const std::size_t FunctorContainer<_signature...>::m_containerId = g_containerId++;


	template<class ..._signature>
	std::vector<typename FunctorContainer<_signature...>::FunctorType> FunctorContainer<_signature...>::m_functors;


	template<class ..._signature>
	inline const std::size_t& FunctorContainer<_signature...>::getContainerId()
	{
		return m_containerId;
	}


	template<class ..._signature>
	template<class ..._params>
	inline std::unique_ptr<RObject> FunctorContainer<_signature...>::reflectCall(std::size_t pFunctorId, _params ..._args)
	{
		if (pFunctorId < m_functors.size()) {
			return m_functors.at(pFunctorId)(_args...);
		}
		else {
			assert(false && "Throw bad call exception");
		}
		return nullptr;
	}


	template<class ..._signature>
	template<class _recordType>
	inline int FunctorContainer<_signature...>::addConstructor()
	{
		const auto functor = [=](_signature...params)->std::unique_ptr<RObject>
		{
			_recordType* retObj = new _recordType(params...);
			return std::unique_ptr<RObject>(new ReturnObject<_recordType*>(retObj));
		};
		m_functors.push_back(functor);
		return (m_functors.size() - 1);
	}


	template<class ..._signature>
	template<class _returnType>
	inline int FunctorContainer<_signature...>::addFunctor(_returnType(*pFunctor)(_signature...), enable_if_same<_returnType, void> *_)
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
	inline int FunctorContainer<_signature...>::addFunctor(_returnType(*pFunctor)(_signature...), enable_if_notSame<_returnType, void> *_)
	{
		const auto functor = [=](_signature...params)->std::unique_ptr<RObject>
		{
			const auto& retObj = (*pFunctor)(params...);
			return std::unique_ptr<RObject>(new ReturnObject<_returnType>(retObj));
		};
		m_functors.push_back(functor);
		return (m_functors.size() - 1);
	}
}