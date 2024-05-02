#pragma once

#include "ClassReflection.h"

namespace rtl
{
	template<class..._args>
	struct ctorArgs;

	struct ReflClassBuilder
	{
		template<class _classType, class _baseTy>
		constexpr static void buildReflectedInheritance();

		template<class _classType, class..._args>
		constexpr static void buildConstructor();

		template<class _classType>
		constexpr static const ClassReflection<_classType>& buildReflectedInstance(const std::string& pClassName);

		template<class _classType, class..._args>
		constexpr static const unsigned addLambdaWrappedCtor(const unsigned pReflClassId, unsigned& pCtorIdRef,
								     sfinae_typeT<ctorArgs<_args...>, ctorVOID>* p_null = nullptr);

		template<class _classType, class..._args>
		constexpr static const unsigned addLambdaWrappedCtor(const unsigned pReflClassId, unsigned& pCtorIdRef,
								     sfinae_typeT<ctorArgs<_args...>, ctorCOPY>* p_null = nullptr);

		template<class _classType, class..._args>
		constexpr static const unsigned addLambdaWrappedCtor(const unsigned pReflClassId, unsigned& pCtorIdRef,
								     sfinae_typeT<ctorArgs<_args...>, ctorMOVE>* p_null = nullptr);

		template<class _classType, class..._args>
		constexpr static const unsigned addLambdaWrappedCtor(const unsigned pReflClassId, unsigned& pCtorIdRef,
								     sfinae_typeF<ctorArgs<_args...>, ctorVOID>* p_nulla = nullptr,
								     sfinae_typeF<ctorArgs<_args...>, ctorCOPY>* p_nullb = nullptr,
								     sfinae_typeF<ctorArgs<_args...>, ctorMOVE>* p_nullc = nullptr);
	};
}
