#pragma once

#include <cassert>

#include "TypeList.h"
#include "FunctorContainer.h"

namespace rtl {

	extern std::size_t g_containerId;

	template<class ..._signature>
	std::vector<std::function<void(_signature...)>> FunctorContainer<_signature...>::m_functors;

	template<class ..._signature>
	const std::size_t FunctorContainer<_signature...>::m_containerId = g_containerId++;

	template<class ..._signature>
	inline const std::size_t& FunctorContainer<_signature...>::getContainerId()
	{
		return m_containerId;
	}


	template<class ..._signature>
	template<class ..._params>
	inline void FunctorContainer<_signature...>::reflectCall(std::size_t pFunctorId, _params ..._args)
	{
		//resolveCall<TypeList<_params...>, TypeList<_signature...>>(pFunctorId, nullptr, _args...);
		if (pFunctorId < m_functors.size()) {
			std::cout << "\n[resolution successful]";
			m_functors.at(pFunctorId)(_args...);
		}
		else {
			assert(false && "Throw bad call exception");
		}
	}


	template<class ..._signature>
	template<class _recordType>
	inline int FunctorContainer<_signature...>::addConstructor()
	{
		const auto functor = [=](_signature...params)->void
		{
			auto obj = new _recordType(params...);
		};
		m_functors.push_back(functor);
		return (m_functors.size() - 1);
	}


	template<class ..._signature>
	template<class _returnType>
	inline int FunctorContainer<_signature...>::addFunctor(_returnType(*pFunctor)(_signature...))
	{
		const auto functor = [=](_signature...params)->void
		{
			(*pFunctor)(params...);
		};
		m_functors.push_back(functor);
		return (m_functors.size() - 1);
	}
}






//template<class _signListA, class _signListB>
//using enable_if_sign_same = typename std::enable_if< std::is_same<_signListA, _signListB>::value >::type;

//template<class _signListA, class _signListB>
//using enable_if_sign_diff = typename std::enable_if< !std::is_same<_signListA, _signListB>::value >::type;


//template<class ..._signature>
//template<class _signListA, class _signListB, class ..._params>
//inline void FunctorContainer<_signature...>::resolveCall(std::size_t pFunctorId, enable_if_sign_diff<_signListA, _signListB>* _, _params ..._args)
//{
//	std::cout << "\n[resolution un-successful]   expected:(" << _signListB::toString() << "), not(" << _signListA::toString() << ")\n";
//}
//
//
//template<class ..._signature>
//template<class _signListA, class _signListB, class ..._params>
//inline void FunctorContainer<_signature...>::resolveCall(std::size_t pFunctorId, enable_if_sign_same<_signListA, _signListB>* _, _params ..._args)
//{
//	std::cout << "\n[resolution successful]";
//}
