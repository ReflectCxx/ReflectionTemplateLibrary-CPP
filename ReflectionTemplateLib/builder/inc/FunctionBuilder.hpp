#pragma once

#include "FunctionBuilder.h"
#include "FunctorContainer.hpp"

namespace rtl {
	
	namespace builder 
	{
		template<class ..._argsType>
		FunctionBuilder<_argsType...>::FunctionBuilder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction)
			: m_record(pRecord)
			, m_function(pFunction)
			, m_namespace(pNamespace) {

		}


		template<class ..._signature>
		template<class _returnType>
		inline constexpr const access::Function FunctionBuilder<_signature...>::build(_returnType(*pFunctor)(_signature...)) const {
			return FunctionBuilder<>(m_namespace, m_record, m_function).build(pFunctor);
		}


		template<class ..._signature>
		template<class _recordType, class _returnType>
		inline constexpr const access::Function FunctionBuilder<_signature...>::build(_returnType(_recordType::* pFunctor)(_signature...)) const {
			return FunctionBuilder<>(m_namespace, m_record, m_function).build(pFunctor);
		}


		template<class _returnType>
		inline constexpr const access::Function FunctionBuilder<void>::build(_returnType(*pFunctor)()) const
		{
			return FunctionBuilder<>(m_namespace, m_record, m_function).build(pFunctor);
		}


		template<class _recordType, class _returnType>
		inline constexpr const access::Function FunctionBuilder<void>::build(_returnType(_recordType::* pFunctor)()) const 
		{
			return FunctionBuilder<>(m_namespace, m_record, m_function).build(pFunctor);
		}


		template<class _recordType, class ..._ctorSignature>
		inline constexpr const access::Function FunctionBuilder<>::build() const
		{
			return addConstructor<_recordType, _ctorSignature...>(m_namespace, m_record, m_function);
		}


		template<class _returnType, class ..._signature>
		inline constexpr const access::Function FunctionBuilder<>::build(_returnType(*pFunctor)(_signature...)) const
		{
			return addFunctor(m_namespace, m_record, m_function, pFunctor);
		}


		template<class _recordType, class _returnType, class ..._signature>
		inline constexpr const access::Function FunctionBuilder<>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
		{
			return addFunctor(m_namespace, m_record, m_function, pFunctor);
		}


		template<class _returnType, class ..._signature>
		inline const access::Function FunctionBuilder<>::addFunctor(const std::string& pNamespace, const std::string& pClassName,
									  const std::string& pFunctionName, _returnType(*pFunctor)(_signature...)) const
		{
			const std::size_t signatureId = detail::FunctorContainer<_signature...>::getContainerId();
			const std::size_t functorId = detail::FunctorContainer<_signature...>::addFunctor(pFunctor);
			const std::string& typeStr = detail::TypeId<_signature...>::toString();
			const std::string& signature = "(" + (typeStr.empty() ? "void" : typeStr) + ")";
			return access::Function(pNamespace, pClassName, pFunctionName, signature, signatureId, functorId);
		}


		template<class _recordType, class _returnType, class ..._signature>
		inline const access::Function FunctionBuilder<>::addFunctor(const std::string& pNamespace, const std::string& pClassName,
									  const std::string& pFunctionName, _returnType(_recordType::* pFunctor)(_signature...)) const
		{
			const std::size_t signatureId = detail::FunctorContainer<_signature...>::getContainerId();
			const std::size_t functorId = detail::FunctorContainer<_signature...>::addFunctor(pFunctor);
			const std::string& typeStr = detail::TypeId<_signature...>::toString();
			const std::string& signature = "(" + (typeStr.empty() ? "void" : typeStr) + ")";
			return access::Function(pNamespace, pClassName, pFunctionName, signature, signatureId, functorId);
		}


		template<typename _recordType, class ..._ctorSignature>
		inline const access::Function FunctionBuilder<>::addConstructor(const std::string& pNamespace, const std::string& pRecord,
									      const std::string& pCtor) const
		{
			const std::size_t signatureId = detail::FunctorContainer<_ctorSignature...>::getContainerId();
			const std::size_t functorId = detail::FunctorContainer<_ctorSignature...>::template addConstructor<_recordType>();
			const std::string& typeStr = detail::TypeId<_ctorSignature...>::toString();
			const std::string& signature = "(" + (typeStr.empty() ? "void" : typeStr) + ")";
			return access::Function(pNamespace, pRecord, pCtor, signature, signatureId, functorId);
		}
	}
}