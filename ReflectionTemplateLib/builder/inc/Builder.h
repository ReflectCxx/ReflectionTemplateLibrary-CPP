#pragma once

#include "Function.h"
#include "ReflectionBuilder.hpp"

namespace rtl {

	namespace builder 
	{
		template<Member _mType, class ..._signature>
		struct Builder;

		template<>
		struct Builder<Member::Const> : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction);

			template<class _recordType, class _returnType>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)() const) const;

			template<class _recordType, class _returnType, class ..._signature>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...) const) const;
		};


		template<>
		struct Builder<Member::Const, void> : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction);

			template<class _recordType, class _returnType>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)() const) const;
		};


		template<class ..._signature>
		struct Builder<Member::Const, _signature...> : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction);

			template<class _recordType, class _returnType>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...) const) const;
		};


		template<Member _mType>
		struct Builder<_mType, void> : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction);

			template<class _returnType>
			constexpr const access::Function build(_returnType(*pFunctor)()) const;

			template<class _recordType, class _returnType>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)()) const;
		};


		template<Member _mType, class ..._signature>
		struct Builder : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction);

			template<class _returnType>
			constexpr const access::Function build(_returnType(*pFunctor)(_signature...)) const;

			template<class _recordType, class _returnType>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...)) const;
		};


		template<Member _mType>
		struct Builder<_mType> : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction);

			template<class _recordType, class ..._signature>
			constexpr const access::Function build() const;

			template<class _returnType, class ..._signature>
			constexpr const access::Function build(_returnType(*pFunctor)(_signature...)) const;

			template<class _recordType, class _returnType, class ..._signature>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...)) const;
		};
	}
}