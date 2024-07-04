#pragma once

#include "Function.h"

namespace rtl {

	namespace detail 
	{
		class ReflectionBuilder
		{
		protected:

			const std::string& m_record;
			const std::string& m_function;
			const std::string& m_namespace;

			ReflectionBuilder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction);

			template<class _recordType, class ..._ctorSignature>
			const access::Function buildConstructor() const;

			template<class _returnType, class ..._signature>
			const access::Function buildFunctor(_returnType(*pFunctor)(_signature...)) const;

			template<class _recordType, class _returnType, class ..._signature>
			const access::Function buildMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...)) const;

			template<class _recordType, class _returnType, class ..._signature>
			const access::Function buildMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...) const) const;
		};
	}
}