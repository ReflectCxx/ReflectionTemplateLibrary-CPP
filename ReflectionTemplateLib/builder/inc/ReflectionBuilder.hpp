#pragma once

#include "ReflectionBuilder.h"
#include "FunctorContainer.h"
#include "MethodContainer.h"
#include "ConstructorContainer.h"

namespace rtl {
	
	namespace detail 
	{	
		inline ReflectionBuilder::ReflectionBuilder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction)
			: m_record(pRecord)
			, m_function(pFunction)
			, m_namespace(pNamespace) {
		}


		template<typename _recordType, class ..._ctorSignature>
		inline const access::Function ReflectionBuilder::buildConstructor() const
		{
			const std::string& typeStr = detail::TypeId<_ctorSignature...>::toString();
			const std::string& signature = "(" + (typeStr.empty() ? "void" : typeStr) + ")";
			const detail::FunctorId functorId = detail::ConstructorContainer<_ctorSignature...>::template pushBack<_recordType, _ctorSignature...>();
			return access::Function(m_namespace, m_record, m_function, signature, functorId);
		}


		template<class _returnType, class ..._signature>
		inline const access::Function ReflectionBuilder::buildFunctor(_returnType(*pFunctor)(_signature...)) const
		{
			const std::string& typeStr = detail::TypeId<_signature...>::toString();
			const std::string& signature = "(" + (typeStr.empty() ? "void" : typeStr) + ")";
			const detail::FunctorId functorId = detail::FunctorContainer<_signature...>::pushBack(pFunctor);
			return access::Function(m_namespace, m_record, m_function, signature, functorId);
		}


		template<class _recordType, class _returnType, class ..._signature>
		inline const access::Function ReflectionBuilder::buildMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...)) const
		{
			const std::string& typeStr = detail::TypeId<_signature...>::toString();
			const std::string& signature = "(" + (typeStr.empty() ? "void" : typeStr) + ")";
			const detail::FunctorId functorId = detail::MethodContainer<TypeQ::Mute, _signature...>::pushBack(pFunctor);
			return access::Function(m_namespace, m_record, m_function, signature, functorId, TypeQ::Mute);
		}


		template<class _recordType, class _returnType, class ..._signature>
		inline const access::Function ReflectionBuilder::buildMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...) const) const
		{
			const std::string& typeStr = detail::TypeId<_signature...>::toString();
			const std::string& signature = "(" + (typeStr.empty() ? "void" : typeStr) + ")";
			const detail::FunctorId functorId = detail::MethodContainer<TypeQ::Const, _signature...>::pushBack(pFunctor);
			return access::Function(m_namespace, m_record, m_function, signature, functorId, TypeQ::Const);
		}
	}
}