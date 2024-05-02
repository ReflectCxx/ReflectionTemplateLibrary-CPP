#pragma once

#include <cassert>
#include <unordered_map>

#include "ReflExecuter.h"
#include "MethodReflection.hpp"

namespace rtl 
{
	inline Executer::Executer(const ReflMethod& pReflMethod, const unsigned pTargetTypeId, void* pTarget)
	: m_targetObj(pTarget)
	, m_targetTypeId(pTargetTypeId)
	, m_reflMethod(pReflMethod)
	{

	}

	inline ReflExecuter<typeQ::CONST>::ReflExecuter(const ReflMethod& pReflMethod, const unsigned pTargetTypeId, const void* pTarget)
	: Executer(pReflMethod, pTargetTypeId, const_cast<void*>(pTarget))
	{

	}

	inline ReflExecuter<typeQ::MUTABLE>::ReflExecuter(const ReflMethod& pReflMethod, const unsigned pTargetTypeId, void* pTarget)
	: Executer(pReflMethod, pTargetTypeId, pTarget)
	{

	}

	template<class _retType, class ..._args>
	inline _retType ReflExecuter<typeQ::CONST>::invoke(_args...params) const
	{
		const unsigned functorTypeId = MethodReflection<_retType, _args...>::getFunctorTypeId();
		const auto& constFunctorMap = m_reflMethod.getConstFunctorTypeIdIndexMap();
		auto indexItr = constFunctorMap.find(functorTypeId);
		assert(indexItr != constFunctorMap.end() && "Bad function call exception.. abort!");
		return MethodReflection<_retType, _args...>::execute(indexItr->second, m_targetTypeId, static_cast<const void*>(m_targetObj), params...);
	}

	template<class _retType, class ..._args>
	inline _retType ReflExecuter<typeQ::MUTABLE>::invoke(_args ...params) const
	{
		const unsigned functorTypeId = MethodReflection<_retType, _args...>::getFunctorTypeId();
		const auto& functorMap = m_reflMethod.getFunctorTypeIdIndexMap();
		auto indexItr = functorMap.find(functorTypeId);
		if (indexItr == functorMap.end())
		{
			if (m_reflMethod.hasConstOverload())
			{
				const auto& constFunctorMap = m_reflMethod.getConstFunctorTypeIdIndexMap();
				auto indexItr = constFunctorMap.find(functorTypeId);
				assert(indexItr != constFunctorMap.end() && "Bad function call exception.. abort!");
				return MethodReflection<_retType, _args...>::execute(indexItr->second, m_targetTypeId, static_cast<const void*>(m_targetObj), params...);
			}
			assert(false && "Bad function call exception.. abort!");
		}
		return MethodReflection<_retType, _args...>::execute(indexItr->second, m_targetTypeId, m_targetObj, params...);
	}
}
