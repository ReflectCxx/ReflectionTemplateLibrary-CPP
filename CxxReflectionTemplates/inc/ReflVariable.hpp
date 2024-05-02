#pragma once

#include "ReflVariable.h"

namespace rtl {
	
	template<class _fieldType>
	inline void ReflVariable::set()
	{
	}

	template<class _fieldType>
	inline void ReflVariable::get()
	{
	}
	
	template<class _classType, class _fieldType>
	inline const ReflVariable ReflVariable::init(_fieldType _classType::* pFieldOffset)
	{
		//const auto functor = [=](void* pTarget, _args... params)
		//{
		//	return	((static_cast<_classType*>(pTarget))->*pFunctor)(params...);
		//};
		//const unsigned int functorId = FunctionReflection<_retType, _args...>::addFunction(pFunctor, functor);
		//return RtMetaFunction(functorId);

		return ReflVariable();
	}
}