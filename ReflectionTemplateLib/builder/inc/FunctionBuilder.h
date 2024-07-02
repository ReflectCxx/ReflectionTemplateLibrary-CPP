#pragma once

#include "Function.h"

namespace rtl {

	namespace builder 
	{
		template<class ..._signature>
		class FunctionBuilder;

		template<>
		class FunctionBuilder<>
		{
			const std::string& m_record;
			const std::string& m_function;
			const std::string& m_namespace;

		public:

			FunctionBuilder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction);

			template<class _recordType, class ..._signature>
			inline constexpr const access::Function build() const;

			template<class _returnType, class ..._signature>
			inline constexpr const access::Function build(_returnType(*pFunctor)(_signature...)) const;

			template<class _recordType, class _returnType, class ..._signature>
			inline constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...)) const;

			template<class _recordType, class _returnType, class ..._signature>
			inline constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...) const) const;

			template<class _recordType, class _returnType, class ..._signature>
			const access::Function buildMethodFunctor(const std::string& pNamespace, const std::string& pRecord,
								  const std::string& pFunction, _returnType(_recordType::* pFunctor)(_signature...) const) const;

		private:

			template<class _returnType, class ..._signature>
			const access::Function buildFunctor(const std::string& pNamespace, const std::string& pRecord,
							    const std::string& pFunction, _returnType(*pFunctor)(_signature...)) const;

			template<class _recordType, class _returnType, class ..._signature>
			const access::Function buildMethodFunctor(const std::string& pNamespace, const std::string& pRecord,
								  const std::string& pFunction, _returnType(_recordType::* pFunctor)(_signature...)) const;

			template<class _recordType, class ..._ctorSignature>
			const access::Function buildConstructor(const std::string& pNamespace, const std::string& pRecord, const std::string& pCtor) const;
		};


		template<class ..._signature>
		class FunctionBuilder
		{
			const std::string& m_record;
			const std::string& m_function;
			const std::string& m_namespace;

		public:

			FunctionBuilder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction);

			template<class _returnType>
			inline constexpr const access::Function build(_returnType(*pFunctor)(_signature...)) const;

			template<class _recordType, class _returnType>
			inline constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...)) const;

			template<class _recordType, class _returnType>
			inline constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...) const) const;
		};


		template<>
		class FunctionBuilder<void>
		{
			const std::string& m_record;
			const std::string& m_function;
			const std::string& m_namespace;

		public:

			FunctionBuilder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction);

			template<class _returnType>
			inline constexpr const access::Function build(_returnType(*pFunctor)()) const;

			template<class _recordType, class _returnType>
			inline constexpr const access::Function build(_returnType(_recordType::* pFunctor)()) const;

			template<class _recordType, class _returnType>
			inline constexpr const access::Function build(_returnType(_recordType::* pFunctor)() const) const;
		};
	}
}