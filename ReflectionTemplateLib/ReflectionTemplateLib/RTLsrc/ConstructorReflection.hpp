#pragma once

#include <cassert>

#include "ClassReflection.h"
#include "ConstructorReflection.h"

namespace rtl {

	template<class _retTy, class..._args>
	const unsigned ConstructorReflection<_retTy, _args...>::m_constructorTypeId = CtorIdCreater::m_ctorIdCounter++;

	template<class _retTy, class..._args>
	std::vector< std::pair< unsigned, CtorFunctor<_retTy, _args...>>> ConstructorReflection<_retTy, _args...>::m_ctorFunctors;

	template<class _retTy, class ..._args>
	inline const unsigned ConstructorReflection<_retTy, _args...>::getConstructorTypeId()
	{
		return m_constructorTypeId;
	}

	template<class _retTy, class..._args>
	template<class _lambdaTy>
	inline const unsigned ConstructorReflection<_retTy, _args...>::add(const unsigned pReflClassId, _lambdaTy pCtorLambda)
	{
		m_ctorFunctors.push_back(std::make_pair(pReflClassId, pCtorLambda));
		return static_cast<unsigned>(m_ctorFunctors.size() - 1);
	}

	template<class _retTy, class..._args>
	inline void* ConstructorReflection<_retTy, _args...>::invoke(const unsigned pReflClassId, const unsigned pCtorIndex, _args ...params)
	{
		assert(pCtorIndex < m_ctorFunctors.size() && "Bad constructor call exception.. abort!");
		auto& constructor = m_ctorFunctors.at(pCtorIndex);
		assert(constructor.first == pReflClassId && "Bad constructor call exception.. abort!");
		return constructor.second(params...);
	}
}