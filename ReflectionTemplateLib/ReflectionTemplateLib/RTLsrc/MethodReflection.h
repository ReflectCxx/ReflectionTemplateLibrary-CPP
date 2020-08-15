#pragma once

#include <functional>
#include <vector>
#include "TypeConstants.h"

namespace rtl {

	struct MethodIdCreater
	{
		static unsigned m_methodIdCounter;
	};

	template<class _retTy, class... _args>
	class MethodReflection
	{
		static const unsigned m_methodTypeId;
		static std::vector< std::pair< ReflMethodId, std::function<_retTy(const unsigned, void*, _args...)>>> m_functors;
		static std::vector< std::pair< ReflMethodId, std::function<_retTy(const unsigned, const void*, _args...)>>> m_constFunctors;

	public:

		MethodReflection() = delete;

		static const unsigned getFunctorTypeId();

		static _retTy execute(const std::pair<ReflMethodId, FunctorIndex>& pFuncIdIndexPair, 
				      const unsigned pTargetTypeId, void* pTarget, _args... params);

		static _retTy execute(const std::pair<ReflMethodId, FunctorIndex>& pFuncIdIndexPair, 
				      const unsigned pTargetTypeId, const void* pTarget, _args... params);

		template<typeQ _funcTy, class _lambdaTy>
		static const unsigned addLambdaWrappedFunctor(const ReflMethodId pReflMethodId, _lambdaTy pFunctor,
							      sfinae_typeQT<_funcTy, typeQ::CONST>* p_null = nullptr);
		template<typeQ _funcTy, class _lambdaTy>
		static const unsigned addLambdaWrappedFunctor(const ReflMethodId pReflMethodId, _lambdaTy pFunctor,
							      sfinae_typeQT<_funcTy, typeQ::MUTABLE>* p_null = nullptr);
	};
}
