#pragma once

#include <string>
#include <memory>

#include "Constants.h"

namespace rtl {

	class RObject;
	class MethodInvoker;
	class FunctionBuilder;

	class Function
	{
		const std::size_t m_functorId;
		const std::size_t m_signatureId;

		const std::string m_record;
		const std::string m_function;
		const std::string m_signature;
		const std::string m_namespace;

		Function(const std::string& pNamespace, const std::string& pClassName, const std::string& pFuncName, 
			 const std::string& pSignature, const std::size_t& pSignatureId, const std::size_t& pFunctorId);

		template<class ..._args>
		std::unique_ptr<RObject> execute(const std::unique_ptr<RObject>& pTarget, _args...params) const;

	public: friend MethodInvoker; friend FunctionBuilder;

		Function() = delete;

		GETTER(std::size_t, FunctorId, m_functorId)
		GETTER(std::size_t, SignatureId, m_signatureId)
		GETTER(std::string, RecordName, m_record)
		GETTER(std::string, FunctionName, m_function)
		GETTER(std::string, Signature, m_signature)
		GETTER(std::string, Namespace, m_namespace)

		template<class ..._args>
		std::unique_ptr<RObject> execute(_args...params) const;
	};
}