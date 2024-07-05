#pragma once

#include "Builder.h"

namespace rtl {

	namespace builder
	{
		inline Builder<Member::Const>::Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}

		template<class _recordType, class _returnType>
		inline constexpr const access::Function Builder<Member::Const>::build(_returnType(_recordType::* pFunctor)() const) const
		{
			return buildMethodFunctor(pFunctor);
		}

		template<class _recordType, class _returnType, class ..._signature>
		inline constexpr const access::Function Builder<Member::Const>::build(_returnType(_recordType::* pFunctor)(_signature...) const) const
		{
			return buildMethodFunctor(pFunctor);
		}
	}


	namespace builder
	{
		inline Builder<Member::Const, void>::Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}

		template<class _recordType, class _returnType>
		inline constexpr const access::Function Builder<Member::Const, void>::build(_returnType(_recordType::* pFunctor)() const) const
		{
			return buildMethodFunctor(pFunctor);
		}
	} 
	

	namespace builder 
	{
		template<class ..._signature>
		inline Builder<Member::Const, _signature...>::Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}

		template<class ..._signature>
		template<class _recordType, class _returnType>
		inline constexpr const access::Function Builder<Member::Const, _signature...>::build(_returnType(_recordType::* pFunctor)(_signature...) const) const
		{
			return buildMethodFunctor(pFunctor);
		}
	}


	namespace builder
	{
		template<Member _mType>
		inline Builder<_mType>::Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}

		template<Member _mType>
		template<class _recordType, class ..._ctorSignature>
		inline constexpr const access::Function Builder<_mType>::build() const
		{
			return buildConstructor<_recordType, _ctorSignature...>();
		}

		template<Member _mType>
		template<class _returnType, class ..._signature>
		inline constexpr const access::Function Builder<_mType>::build(_returnType(*pFunctor)(_signature...)) const
		{
			return buildFunctor(pFunctor);
		}

		template<Member _mType>
		template<class _recordType, class _returnType, class ..._signature>
		inline constexpr const access::Function Builder<_mType>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
		{
			return buildMethodFunctor(pFunctor);
		}
	}
	

	namespace builder
	{
		template<Member _mType>
		inline Builder<_mType, void>::Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}

		template<Member _mType>
		template<class _returnType>
		inline constexpr const access::Function Builder<_mType, void>::build(_returnType(*pFunctor)()) const
		{
			return buildFunctor(pFunctor);
		}

		template<Member _mType>
		template<class _recordType, class _returnType>
		inline constexpr const access::Function Builder<_mType, void>::build(_returnType(_recordType::* pFunctor)()) const
		{
			return buildMethodFunctor(pFunctor);
		}
	}


	namespace builder
	{
		template<Member _mType, class ..._signature>
		inline Builder<_mType, _signature...>::Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}

		template<Member _mType, class ..._signature>
		template<class _returnType>
		inline constexpr const access::Function Builder<_mType, _signature...>::build(_returnType(*pFunctor)(_signature...)) const
		{
			return buildFunctor(pFunctor);
		}
		
		template<Member _mType, class ..._signature>
		template<class _recordType, class _returnType>
		inline constexpr const access::Function Builder<_mType, _signature...>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
		{
			return buildMethodFunctor(pFunctor);
		}
	}
}