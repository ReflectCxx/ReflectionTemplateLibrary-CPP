#pragma once

#include <vector>

#include "TypeConstants.h"

namespace rtl {

	class ReflClass;
	struct ReflClassBuilder;

	struct CtorIdCreater
	{
		static unsigned m_ctorIdCounter;
	};

	template<class _retTy, class..._args>
	class ConstructorReflection 
	{
		friend ReflClass;
		friend ReflClassBuilder;

		static const unsigned m_constructorTypeId;

		static std::vector< std::pair< unsigned, CtorFunctor<_retTy, _args...>>> m_ctorFunctors;

		ConstructorReflection() = delete;

		static const unsigned getConstructorTypeId();
		static void* invoke(const unsigned pReflClassId, const unsigned pCtorIndex, _args... params);

		template<class _lambdaTy>
		static const unsigned add(const unsigned pReflClassId, _lambdaTy pCtorLambda);
	};
}