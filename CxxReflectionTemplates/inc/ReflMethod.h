#pragma once

#include <map>
#include <functional>
#include <unordered_map>

#include "ReflObject.h"
#include "ReflExecuter.h"
#include "TypeConstants.h"

namespace rtl {
	
	class ReflClass;
	
	class ReflMethod 
	{
		static ReflMethodId m_instanceCount;

		mutable bool m_isAmbiguous;
		mutable bool m_hasConstOverload;
		mutable const ReflClass* m_ownerReflClass;
		mutable FunctorTypeIdIndexMap m_functorTypeIdIndexMap;
		mutable FunctorTypeIdIndexMap m_constFunctorTypeIdIndexMap;

		void setOwnerClass(const ReflClass& pOwnerClass) const;
		void mergeOverloads(const ReflMethod& pSrcFunction) const;
		void mergeInheritedOverloads(const ReflMethod& pSrcFunction, const bool pIsOwnerOtherBase) const;

		ReflMethod(const FunctorTypeId pFunctorTypeId, const FunctorIndex pFunctorIndex);
		ReflMethod(const FunctorTypeId pFunctorTypeId, const FunctorIndex pFunctorIndex, const bool pIsConstMethod);

	public: friend ReflClass;

		ReflMethod() = delete;

		const bool isAmbiguous() const;
		const bool hasConstOverload() const;
		const FunctorTypeIdIndexMap& getFunctorTypeIdIndexMap() const;
		const FunctorTypeIdIndexMap& getConstFunctorTypeIdIndexMap() const;

		template<class _classTy, class _retTy, class... _args>
		static const ReflMethod init(_retTy(_classTy::* pFunctor)(_args...));

		template<class _classTy, class _retTy, class... _args>
		static const ReflMethod init(_retTy(_classTy::* pFunctor)(_args...) const);

		template<class _objTy>
		const ReflExecuter<typeQ::MUTABLE> operator()(const ReflObject<_objTy>& pTargetReflObj) const;

		template<class _objTy>
		const ReflExecuter<typeQ::CONST> operator()(const ReflObject<const _objTy>& pTargetReflObj) const;
	};
}