#include <cassert>
#include <vector>

#include "ReflMethod.h"
#include "ReflClass.h"
#include "ReflClass.hpp"

using namespace std;

namespace rtl {	

	unsigned ReflMethod::m_instanceCount = 0;

	ReflMethod::ReflMethod(const FunctorTypeId pFunctorTypeId, const FunctorIndex pFunctorIndex)
	: m_functorTypeIdIndexMap{ make_pair(pFunctorTypeId, make_pair(m_instanceCount++, pFunctorIndex)) }
	, m_hasConstOverload(false)
	, m_isAmbiguous(false)
	{
	}

	ReflMethod::ReflMethod(const FunctorTypeId pFunctorTypeId, const FunctorIndex pFunctorIndex, const bool pIsConstMethod)
	: m_constFunctorTypeIdIndexMap{ make_pair(pFunctorTypeId, make_pair(m_instanceCount++, pFunctorIndex)) }
	, m_hasConstOverload(pIsConstMethod)
	, m_isAmbiguous(false)
	{
	}

	void ReflMethod::mergeOverloads(const ReflMethod& pSrcFunction) const
	{
		m_functorTypeIdIndexMap.insert(pSrcFunction.m_functorTypeIdIndexMap.begin(), pSrcFunction.m_functorTypeIdIndexMap.end());
		m_constFunctorTypeIdIndexMap.insert(pSrcFunction.m_constFunctorTypeIdIndexMap.begin(), pSrcFunction.m_constFunctorTypeIdIndexMap.end());
		m_hasConstOverload = !m_constFunctorTypeIdIndexMap.empty();
	}

	void ReflMethod::mergeInheritedOverloads(const ReflMethod& pSrcFunction, const bool pIsAlreadyInherited) const
	{
		vector<FunctorTypeId> failedOverloadIds;
		vector<FunctorTypeId> failedConstOverloadIds;

		for (const auto& itr : pSrcFunction.m_functorTypeIdIndexMap)
		{
			const FunctorTypeId fnctrTypeId = itr.first;
			if (m_functorTypeIdIndexMap.find(fnctrTypeId) == m_functorTypeIdIndexMap.end())
			{
				m_functorTypeIdIndexMap.emplace(itr);
			}
			else failedOverloadIds.push_back(fnctrTypeId);
		}
		for (const auto& itr : pSrcFunction.m_constFunctorTypeIdIndexMap)
		{
			const FunctorTypeId fnctrTypeId = itr.first;
			if (m_constFunctorTypeIdIndexMap.find(fnctrTypeId) == m_constFunctorTypeIdIndexMap.end())
			{
				m_constFunctorTypeIdIndexMap.emplace(itr);
			}
			else failedConstOverloadIds.push_back(fnctrTypeId);
		}

		m_isAmbiguous = false;
		if (pIsAlreadyInherited && !(failedOverloadIds.empty() && failedConstOverloadIds.empty()))
		{
			if (m_ownerReflClass != pSrcFunction.m_ownerReflClass) 
			{
				if (m_ownerReflClass->isCastSafeToTypeId(pSrcFunction.m_ownerReflClass->getReflClassId())) 
				{
					for (const FunctorTypeId fnctorTypeId : failedOverloadIds) 
					{
						m_functorTypeIdIndexMap.at(fnctorTypeId) = pSrcFunction.m_functorTypeIdIndexMap.at(fnctorTypeId);
					}
					for (const FunctorTypeId fnctorTypeId : failedConstOverloadIds)
					{
						m_constFunctorTypeIdIndexMap.at(fnctorTypeId) = pSrcFunction.m_constFunctorTypeIdIndexMap.at(fnctorTypeId);
					}
				}
				else
				{
					m_isAmbiguous = true;
				}
			}
		}
		m_hasConstOverload = !m_constFunctorTypeIdIndexMap.empty();
	}
}