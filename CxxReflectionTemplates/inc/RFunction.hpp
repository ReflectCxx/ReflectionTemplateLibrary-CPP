#pragma once

#include "RFunction.h"
#include "ReflectionDescriptor.h"

namespace rtl_basic {

	template<class ..._signature>
	inline void RFunction::execute(_signature ..._params)
	{
		SignatureDescriptor::call(m_signatureId, m_functorId, _params...);
	}


	template<class _returnType, class ..._signature>
	inline RFunction rtl_basic::RFunction::add(const std::string& pFunctionName, _returnType(*pFunctor)(_signature...))
	{
		const std::size_t signatureId = FunctorContainer<_signature...>::getContainerId();
		const std::size_t functorId = FunctorContainer<_signature...>::addFunctor(pFunctor);
		return RFunction(signatureId, functorId, pFunctionName);
	}
}