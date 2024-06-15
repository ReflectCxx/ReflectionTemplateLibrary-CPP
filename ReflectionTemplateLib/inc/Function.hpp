#pragma once

#include "Function.h"
#include "FunctorContainer.hpp"

namespace rtl {

	template<class _returnType, class ..._signature>
	inline const Function Function::add(const std::string& pNamespace, const std::string& pClassName, 
										const std::string& pFunctionName, _returnType(*pFunctor)(_signature...))
	{
		const std::size_t signatureId = FunctorContainer<_signature...>::getContainerId();
		const std::size_t functorId = FunctorContainer<_signature...>::addFunctor(pFunctor);
		return Function(pNamespace, pClassName, signatureId, functorId, pFunctionName);
	}
}