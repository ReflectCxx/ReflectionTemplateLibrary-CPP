#pragma once

#include "Function.h"
#include "ReflectionBuilder.hpp"

namespace rtl {

	namespace builder 
	{
		template<TypeQ _typeQ, class ..._signature>
		struct Builder;
	}


	namespace builder
	{
		template<>
		struct Builder<TypeQ::None, void> : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord,
				const std::string& pFunction, bool& pBuildDctor);

			template<class _returnType>
			constexpr const access::Function build(_returnType(*pFunctor)()) const;
		};


		template<class ..._signature>
		struct Builder<TypeQ::None, _signature...> : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord,
				const std::string& pFunction, bool& pBuildDctor);

			template<class _returnType>
			constexpr const access::Function build(_returnType(*pFunctor)(_signature...)) const;
		};


		template<>
		struct Builder<TypeQ::None> : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord,
				const std::string& pFunction, bool& pBuildDctor);

			template<class _returnType, class ..._signature>
			constexpr const access::Function build(_returnType(*pFunctor)(_signature...)) const;
		};
	}


	namespace builder
	{
		template<>
		struct Builder<TypeQ::Const, void> : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord,
				const std::string& pFunction, bool& pBuildDctor);

			template<class _recordType, class _returnType>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)() const) const;
		};


		template<class ..._signature>
		struct Builder<TypeQ::Const, _signature...> : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord,
				const std::string& pFunction, bool& pBuildDctor);

			template<class _recordType, class _returnType>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...) const) const;
		};


		template<>
		struct Builder<TypeQ::Const> : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord,
				const std::string& pFunction, bool& pBuildDctor);

			template<class _recordType, class _returnType>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)() const) const;

			template<class _recordType, class _returnType, class ..._signature>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...) const) const;
		};
	}

	
	namespace builder 
	{
		template<>
		struct Builder<TypeQ::Mute, void> : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord,
				const std::string& pFunction, bool& pBuildDctor);

			template<class _recordType, class _returnType>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)()) const;
		};


		template<class ..._signature>
		struct Builder<TypeQ::Mute, _signature...> : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord,
				const std::string& pFunction, bool& pBuildDctor);

			template<class _recordType, class _returnType>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...)) const;
		};


		template<>
		struct Builder<TypeQ::Mute> : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord,
				const std::string& pFunction, bool& pBuildDctor);

			template<class _recordType, class ..._signature>
			constexpr const access::Function build(const FunctorType& pCtorType) const;

			template<class _recordType, class _returnType, class ..._signature>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...)) const;
		};
	}
}