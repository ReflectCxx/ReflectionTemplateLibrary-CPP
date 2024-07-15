#pragma once

#include "ReflectionBuilder.h"
#include "FunctorContainer.h"
#include "MethodContainer.h"

namespace rtl {
	
	namespace detail 
	{	
		inline ReflectionBuilder::ReflectionBuilder(const std::string& pNamespace, const std::string& pRecord, 
							    const std::string& pFunction)
			: m_record(pRecord)
			, m_function(pFunction)
			, m_namespace(pNamespace) {
		}


		template<class _returnType, class ..._signature>
		inline const access::Function ReflectionBuilder::buildFunctor(_returnType(*pFunctor)(_signature...)) const
		{
			const std::string& typeStr = detail::TypeId<_signature...>::toString();
			const std::string& signature = "(" + (typeStr.empty() ? "void" : typeStr) + ")";
			const detail::FunctorId functorId = detail::FunctorContainer<_signature...>::addFunctor(pFunctor);
			return access::Function(m_namespace, m_record, m_function, signature, functorId, TypeId<>::None, TypeQ::None);
		}


		template<class _recordType, class _returnType, class ..._signature>
		inline const access::Function ReflectionBuilder::buildMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...)) const
		{
			const std::string& typeStr = detail::TypeId<_signature...>::toString();
			const std::string& signature = "(" + (typeStr.empty() ? "void" : typeStr) + ")";
			const detail::FunctorId functorId = detail::MethodContainer<TypeQ::Mute, _signature...>::addFunctor(pFunctor);
			return access::Function(m_namespace, m_record, m_function, signature, functorId, TypeId<_recordType>::get(), TypeQ::Mute);
		}


		template<class _recordType, class _returnType, class ..._signature>
		inline const access::Function ReflectionBuilder::buildMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...) const) const
		{
			const std::string& typeStr = detail::TypeId<_signature...>::toString();
			const std::string& signature = "(" + (typeStr.empty() ? "void" : typeStr) + ")";
			const detail::FunctorId functorId = detail::MethodContainer<TypeQ::Const, _signature...>::addFunctor(pFunctor);
			return access::Function(m_namespace, m_record, m_function, signature, functorId, TypeId<_recordType>::get(), TypeQ::Const);
		}


		template<typename _recordType, class ..._ctorSignature>
		inline const access::Function ReflectionBuilder::buildConstructor() const
		{
			const detail::FunctorId functorId = detail::FunctorContainer<_ctorSignature...>::template addConstructor<_recordType, _ctorSignature...>();
			const std::string& typeStr = detail::TypeId<_ctorSignature...>::toString();
			const std::string& signature = "(" + (typeStr.empty() ? "void" : typeStr) + ")";
			const access::Function constructor = access::Function(m_namespace, m_record, m_function, signature, functorId, TypeId<_recordType>::get(), TypeQ::None);
			constructor.getFunctorIds().emplace_back(detail::FunctorContainer<std::any>::addDestructor<_recordType>());
			return constructor;
		}


		template<class _recordType, class ..._ctorSignature>
		inline const access::Function ReflectionBuilder::buildCopyConstructor() const
		{
			const detail::FunctorId functorId = detail::FunctorContainer<std::any>::addCopyConstructor<_recordType>();
			const std::string& typeStr = detail::TypeId<_ctorSignature...>::toString();
			const std::string& signature = "(" + (typeStr.empty() ? "void" : typeStr) + ")";
			const access::Function constructor = access::Function(m_namespace, m_record, m_function, signature, functorId, TypeId<_recordType>::get(), TypeQ::None);
			constructor.getFunctorIds().emplace_back(detail::FunctorContainer<std::any>::addDestructor<_recordType>());
			return constructor;
		}
		
		
		template<class _recordType, class ..._ctorSignature>
		inline const access::Function ReflectionBuilder::buildConstCopyConstructor() const
		{
			const detail::FunctorId functorId = detail::FunctorContainer<std::any>::addConstCopyConstructor<_recordType>();
			const std::string& typeStr = detail::TypeId<_ctorSignature...>::toString();
			const std::string& signature = "(" + (typeStr.empty() ? "void" : typeStr) + ")";
			const access::Function constructor = access::Function(m_namespace, m_record, m_function, signature, functorId, TypeId<_recordType>::get(), TypeQ::None);
			constructor.getFunctorIds().emplace_back(detail::FunctorContainer<std::any>::addDestructor<_recordType>());
			return constructor;
		}
	}
}