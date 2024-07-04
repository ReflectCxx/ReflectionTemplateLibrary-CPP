#pragma once

#include "Builder.h"

namespace rtl {

	namespace builder
	{
		inline Builder<>::Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction) 
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}


		template<class _recordType, class ..._ctorSignature>
		inline constexpr const access::Function Builder<>::build() const
		{
			return buildConstructor<_recordType, _ctorSignature...>();
		}


		template<class _returnType, class ..._signature>
		inline constexpr const access::Function Builder<>::build(_returnType(*pFunctor)(_signature...)) const
		{
			return buildFunctor(pFunctor);
		}


		template<class _recordType, class _returnType, class ..._signature>
		inline constexpr const access::Function Builder<>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
		{
			return buildMethodFunctor(pFunctor);
		}


		template<class _recordType, class _returnType, class ..._signature>
		inline constexpr const access::Function Builder<>::build(_returnType(_recordType::* pFunctor)(_signature...) const) const
		{
			return buildMethodFunctor(pFunctor);
		}


		template<class _recordType, class _returnType, class ..._signature>
		inline constexpr const access::Function Builder<>::buildConst(_returnType(_recordType::* pFunctor)(_signature...) const) const
		{
			return buildMethodFunctor(pFunctor);
		}
	}
	

	namespace builder
	{
		inline Builder<void>::Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}


		template<class _returnType>
		inline constexpr const access::Function Builder<void>::build(_returnType(*pFunctor)()) const
		{
			return buildFunctor(pFunctor);
		}

		
		template<class _recordType, class _returnType>
		inline constexpr const access::Function Builder<void>::build(_returnType(_recordType::* pFunctor)()) const
		{
			return buildMethodFunctor(pFunctor);
		}


		template<class _recordType, class _returnType>
		inline constexpr const access::Function Builder<void>::build(_returnType(_recordType::* pFunctor)() const) const
		{
			return buildMethodFunctor(pFunctor);
		}
	}


	namespace builder
	{
		template<class ..._argsType>
		inline Builder<_argsType...>::Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}


		template<class ..._signature>
		template<class _returnType>
		inline constexpr const access::Function Builder<_signature...>::build(_returnType(*pFunctor)(_signature...)) const 
		{
			return buildFunctor(pFunctor);
		}

		
		template<class ..._signature>
		template<class _recordType, class _returnType>
		inline constexpr const access::Function Builder<_signature...>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
		{
			return buildMethodFunctor(pFunctor);
		}


		template<class ..._signature>
		template<class _recordType, class _returnType>
		inline constexpr const access::Function Builder<_signature...>::build(_returnType(_recordType::* pFunctor)(_signature...) const) const
		{
			return buildMethodFunctor(pFunctor);
		}
	}
}