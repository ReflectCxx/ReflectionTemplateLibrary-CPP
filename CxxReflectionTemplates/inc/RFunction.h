//#pragma once
//
//#include <string>
//
//namespace rtl_basic {
//
//	class RFunction
//	{
//		std::size_t m_functorId;
//		std::size_t m_signatureId;
//		std::string m_functionName;
//
//		RFunction(const std::size_t& pSignatureId, const std::size_t& pFunctorId, const std::string& pFuncName);
//
//	public:
//
//		const std::string& getFunctionName();
//
//		template<class _returnType, class ..._signature>
//		static RFunction add(const std::string& pFunctionName, _returnType(*pFunctor)(_signature...));
//
//		template<class ..._signature>
//		void execute(_signature..._params);
//	};
//}