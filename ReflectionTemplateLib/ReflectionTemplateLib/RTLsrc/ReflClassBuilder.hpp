#pragma once

#include "ReflClassBuilder.h"
#include "ConstructorReflection.h"

namespace rtl 
{
	template<class _classTy>
	constexpr const ClassReflection<_classTy>& ReflClassBuilder::buildReflectedInstance(const std::string& pClassName)
	{
		ClassReflection<_classTy>::Instance.initInstance(pClassName);
		return ClassReflection<_classTy>::Instance;
	}

	template<class _classTy, class _baseTy>
	inline constexpr  void ReflClassBuilder::buildReflectedInheritance()
	{
		ClassReflection<_classTy>::Instance.template initReflectedInheritance<_classTy, _baseTy>();
	}

	template<class _classTy, class..._args>
	inline constexpr  void ReflClassBuilder::buildConstructor()
	{
		unsigned ctorTypeIdRef = -1;
		const unsigned reflClassId = ClassReflection<_classTy>::Instance.getReflClassId();
		const unsigned ctorIndex = addLambdaWrappedCtor<_classTy, _args...>(reflClassId, ctorTypeIdRef);
		if (ctorIndex != -1)
		{
			ClassReflection<_classTy>::Instance.initReflectedConstructor(ctorTypeIdRef, ctorIndex);
		}
	}

	template<class _classTy, class..._args>
	inline constexpr  const unsigned ReflClassBuilder::addLambdaWrappedCtor(const unsigned pReflClassId, unsigned& pCtorIdRef,
																 sfinae_typeT<ctorArgs<_args...>, ctorMOVE>* p_null)
	{
		static_assert(false, "ctor::MOVE - move constructor reflection is not supported yet");
	}

	template<class _classTy, class..._args>
	inline constexpr const unsigned ReflClassBuilder::addLambdaWrappedCtor(const unsigned pReflClassId, unsigned& pCtorIdRef,
																 sfinae_typeT<ctorArgs<_args...>, ctorVOID>* p_null)
	{
		pCtorIdRef = ConstructorReflection<void*, _args...>::getConstructorTypeId();
		return ConstructorReflection<void*, _args...>::template add( pReflClassId,
		[]()
		{
			return static_cast<void*>(new _classTy());
		});
	}

	template<class _classTy, class..._args>
	inline constexpr const unsigned ReflClassBuilder::addLambdaWrappedCtor(const unsigned pReflClassId, unsigned& pCtorIdRef,
																 sfinae_typeT<ctorArgs<_args...>, ctorCOPY>* p_null)
	{
		pCtorIdRef = ConstructorReflection<void*, void*, ctorCOPY*>::getConstructorTypeId();
		return ConstructorReflection<void*, void*, ctorCOPY*>::template add( pReflClassId,
		[](void *pSrcObj, ctorCOPY* p_null)
		{
			_classTy& srcObj = *(static_cast<_classTy*>(pSrcObj));
			return static_cast<void*>(new _classTy(srcObj));
		});
	}

	template<class _classTy, class..._args>
	inline constexpr const unsigned ReflClassBuilder::addLambdaWrappedCtor(const unsigned pReflClassId, unsigned& pCtorIdRef,
																 sfinae_typeF<ctorArgs<_args...>, ctorVOID>* p_nulla,
																 sfinae_typeF<ctorArgs<_args...>, ctorCOPY>* p_nullb,
																 sfinae_typeF<ctorArgs<_args...>, ctorMOVE>* p_nullc)
	{
		pCtorIdRef = ConstructorReflection<void*, _args...>::getConstructorTypeId();
		return ConstructorReflection<void*, _args...>::template add( pReflClassId,
		[](_args...params)
		{
			return static_cast<void*>(new _classTy(params...));
		});
	}
}

