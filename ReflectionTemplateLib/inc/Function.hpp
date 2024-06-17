#pragma once

#include "Function.h"
#include "Constants.h"
#include "FunctorContainer.hpp"

namespace rtl {
	
	template<class ..._args>
	inline void Function::execute(_args ...params) const
	{
		if (m_signatureId == FunctorContainer<_args...>::getContainerId()) {
			FunctorContainer<_args...>::dispatchCall(m_functorId, params...);
		}
		else {
			assert(false && "Throw bad call exception");
		}
	}


	template<typename _recordType, class ..._ctorSignature>
	inline const Function Function::addConstructor(const std::string& pNamespace, const std::string& pRecord)
	{
		const std::size_t signatureId = FunctorContainer<_ctorSignature...>::getContainerId();
		const std::size_t functorId = FunctorContainer<_ctorSignature...>::template addConstructor<_recordType>();
		return Function(pNamespace, pRecord, signatureId, functorId, (pRecord + CTOR_SUFFIX));
	}


	template<class _returnType, class ..._signature>
	inline const Function Function::addFunctor(const std::string& pNamespace, const std::string& pClassName, const std::string& pFunctionName, _returnType(*pFunctor)(_signature...))
	{
		const std::size_t signatureId = FunctorContainer<_signature...>::getContainerId();
		const std::size_t functorId = FunctorContainer<_signature...>::addFunctor(pFunctor);
		return Function(pNamespace, pClassName, signatureId, functorId, pFunctionName);
	}
}