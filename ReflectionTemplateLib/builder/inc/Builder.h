#pragma once

#include "Function.h"
#include "ReflectionBuilder.hpp"

namespace rtl {

	namespace builder 
	{
		template<class ..._signature>
		struct Builder;

		template<>
		struct Builder<> : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction);

			template<class _recordType, class ..._signature>
			constexpr const access::Function build() const;

			template<class _returnType, class ..._signature>
			constexpr const access::Function build(_returnType(*pFunctor)(_signature...)) const;

			template<class _recordType, class _returnType, class ..._signature>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...)) const;

			template<class _recordType, class _returnType, class ..._signature>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...) const) const;

			template<class _recordType, class _returnType, class ..._signature>
			constexpr const access::Function buildConst(_returnType(_recordType::* pFunctor)(_signature...) const) const;
		};


		template<class ..._signature>
		struct Builder : protected detail::ReflectionBuilder
		{
			Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction);

			template<class _returnType>
			constexpr const access::Function build(_returnType(*pFunctor)(_signature...)) const;

			template<class _recordType, class _returnType>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...)) const;

			template<class _recordType, class _returnType>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...) const) const;
		};


		template<>
		struct Builder<void> : protected detail::ReflectionBuilder
		{
		public:
			Builder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction);

			template<class _returnType>
			constexpr const access::Function build(_returnType(*pFunctor)()) const;

			template<class _recordType, class _returnType>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)()) const;

			template<class _recordType, class _returnType>
			constexpr const access::Function build(_returnType(_recordType::* pFunctor)() const) const;
		};
	}
}