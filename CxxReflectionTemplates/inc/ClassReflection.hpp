#pragma once;

#include "ClassReflection.h"

namespace rtl {

	template<class _classType>
	const ClassReflection<_classType> ClassReflection<_classType>::Instance;

	template<class _classType>
	ClassReflection<_classType>::ClassReflection() :ReflClass(typeid(_classType).name())
	{
	}

	template<class _classType>
	inline const ClassReflection<_classType>*
	ClassReflection<_classType>::add(const std::multimap<const std::string, const ReflMethod>& pFunctions) const
	{
		initReflectedMethods(pFunctions);
		return this;
	}

	template<class _classType>
	inline const bool ClassReflection<_classType>::isReflTypeIdSame(const unsigned pTypeId)
	{
		return (pTypeId == Instance.getReflClassId());
	}

	template<class _classType>
	inline const InheritanceCastFunctor ClassReflection<_classType>::getSafeUpCastFptr(unsigned pReflTypeId)
	{
		return Instance.m_safeUpCastFunctors.at(pReflTypeId);
	}

	template<class _classType>
	inline void ClassReflection<_classType>::initInstance(const std::string& pClassName) const
	{
		initReflectedTypeName(pClassName);
		initReflectedDestructor(
		[](const void* pTarget)->void
		{
				delete static_cast<const _classType*>(pTarget);
		});
	}
}