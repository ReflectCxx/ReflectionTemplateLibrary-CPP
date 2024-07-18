#pragma once

#include "Builder.h"

namespace rtl {

	namespace builder
	{
		inline Builder<TypeQ::None>::Builder(const std::string& pNamespace, const std::string& pRecord,
						     const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}

		template<class _returnType, class ..._signature>
		inline constexpr const access::Function Builder<TypeQ::None>::build(_returnType(*pFunctor)(_signature...)) const
		{
			return buildFunctor(pFunctor);
		}
	}
	

	namespace builder
	{
		inline Builder<TypeQ::None, void>::Builder(const std::string& pNamespace, const std::string& pRecord,
							   const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}

		template<class _returnType>
		inline constexpr const access::Function Builder<TypeQ::None, void>::build(_returnType(*pFunctor)()) const
		{
			return buildFunctor(pFunctor);
		}
	}


	namespace builder 
	{
		template<class ..._signature>
		inline Builder<TypeQ::None, _signature...>::Builder(const std::string& pNamespace, const std::string& pRecord,
								    const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}

		template<class ..._signature>
		template<class _returnType>
		inline constexpr const access::Function Builder<TypeQ::None, _signature...>::build(_returnType(*pFunctor)(_signature...)) const
		{
			return buildFunctor(pFunctor);
		}
	}


	namespace builder
	{
		inline Builder<TypeQ::Const>::Builder(const std::string& pNamespace, const std::string& pRecord,
						      const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}

		template<class _recordType, class _returnType>
		inline constexpr const access::Function Builder<TypeQ::Const>::build(_returnType(_recordType::* pFunctor)() const) const
		{
			return buildMethodFunctor(pFunctor);
		}

		template<class _recordType, class _returnType, class ..._signature>
		inline constexpr const access::Function Builder<TypeQ::Const>::build(_returnType(_recordType::* pFunctor)(_signature...) const) const
		{
			return buildMethodFunctor(pFunctor);
		}
	}


	namespace builder
	{
		inline Builder<TypeQ::Const, void>::Builder(const std::string& pNamespace, const std::string& pRecord,
							    const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}

		template<class _recordType, class _returnType>
		inline constexpr const access::Function Builder<TypeQ::Const, void>::build(_returnType(_recordType::* pFunctor)() const) const
		{
			return buildMethodFunctor(pFunctor);
		}
	}
	

	namespace builder 
	{
		template<class ..._signature>
		inline Builder<TypeQ::Const, _signature...>::Builder(const std::string& pNamespace, const std::string& pRecord,
								     const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}

		template<class ..._signature>
		template<class _recordType, class _returnType>
		inline constexpr const access::Function Builder<TypeQ::Const, _signature...>::build(_returnType(_recordType::* pFunctor)(_signature...) const) const
		{
			return buildMethodFunctor(pFunctor);
		}
	}


	namespace builder
	{
		inline Builder<TypeQ::Mute>::Builder(const std::string& pNamespace, const std::string& pRecord,
						     const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}


		template<class _recordType, class ..._signature>
		inline constexpr const access::Function Builder<TypeQ::Mute>::build() const
		{
			if constexpr (std::is_same_v<_recordType&, typename detail::TypeId<_signature...>::HEAD>) 
			{
				return buildCopyConstructor<_recordType, _signature...>();
			}
			else if constexpr (std::is_same_v<const _recordType&, typename detail::TypeId<_signature...>::HEAD>) 
			{
				return buildConstCopyConstructor<_recordType, _signature...>();
			}
			else {
				return buildConstructor<_recordType, _signature...>();
			}
		}


		template<class _recordType, class _returnType, class ..._signature>
		inline constexpr const access::Function Builder<TypeQ::Mute>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
		{
			return buildMethodFunctor(pFunctor);
		}
	}
	

	namespace builder
	{
		inline Builder<TypeQ::Mute, void>::Builder(const std::string& pNamespace, const std::string& pRecord,
							   const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}

		template<class _recordType, class _returnType>
		inline constexpr const access::Function Builder<TypeQ::Mute, void>::build(_returnType(_recordType::* pFunctor)()) const
		{
			return buildMethodFunctor(pFunctor);
		}
	}


	namespace builder
	{
		template<class ..._signature>
		inline Builder<TypeQ::Mute, _signature...>::Builder(const std::string& pNamespace, const std::string& pRecord,
								    const std::string& pFunction)
			: ReflectionBuilder(pNamespace, pRecord, pFunction) {
		}
		
		template<class ..._signature>
		template<class _recordType, class _returnType>
		inline constexpr const access::Function Builder<TypeQ::Mute, _signature...>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
		{
			return buildMethodFunctor(pFunctor);
		}
	}
}