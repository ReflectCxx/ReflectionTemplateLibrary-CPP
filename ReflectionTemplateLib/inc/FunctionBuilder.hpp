#pragma once

#include "FunctionBuilder.h"
#include "FunctorContainer.hpp"

namespace rtl {
	
	template<class _recordType, class ..._ctorSignature>
	inline constexpr const Function FunctionBuilder::build() const
	{
		return addConstructor<_recordType, _ctorSignature...>(m_namespace, m_record, m_function);
	}

	template<class _returnType, class ..._signature>
	inline constexpr const Function FunctionBuilder::build(_returnType(*pFunctor)(_signature...)) const
	{
		return addFunctor(m_namespace, m_record, m_function, pFunctor);
	}

	template<class _recordType, class _returnType, class ..._signature>
	inline constexpr const Function FunctionBuilder::build(_returnType(_recordType::* pFunctor)(_signature...)) const
	{
		return addFunctor(m_namespace, m_record, m_function, pFunctor);
	}


	template<class _returnType, class ..._signature>
	inline const Function FunctionBuilder::addFunctor(const std::string& pNamespace, const std::string& pClassName,
							  const std::string& pFunctionName, _returnType(*pFunctor)(_signature...)) const
	{
		const std::size_t signatureId = FunctorContainer<_signature...>::getContainerId();
		const std::size_t functorId = FunctorContainer<_signature...>::addFunctor(pFunctor);
		const std::string& signature = "(" + TypeList<_signature...>::toString() + ")";
		return Function(pNamespace, pClassName, pFunctionName, signature, signatureId, functorId);
	}


	template<class _recordType, class _returnType, class ..._signature>
	inline const Function FunctionBuilder::addFunctor(const std::string& pNamespace, const std::string& pClassName,
							  const std::string& pFunctionName, _returnType(_recordType::* pFunctor)(_signature...)) const
	{
		const std::size_t signatureId = FunctorContainer<_signature...>::getContainerId();
		const std::size_t functorId = FunctorContainer<_signature...>::addFunctor(pFunctor);
		const std::string& signature = "(" + TypeList<_signature...>::toString() + ")";
		return Function(pNamespace, pClassName, pFunctionName, signature, signatureId, functorId);
	}


	template<typename _recordType, class ..._ctorSignature>
	inline const Function FunctionBuilder::addConstructor(const std::string& pNamespace, const std::string& pRecord,
							      const std::string& pCtor) const
	{
		const std::size_t signatureId = FunctorContainer<_ctorSignature...>::getContainerId();
		const std::size_t functorId = FunctorContainer<_ctorSignature...>::template addConstructor<_recordType>();
		const std::string& ctorName = pCtor + std::to_string(signatureId);
		const std::string& signature = "(" + TypeList<_ctorSignature...>::toString() + ")";
		return Function(pNamespace, pRecord, ctorName, signature, signatureId, functorId);
	}
}