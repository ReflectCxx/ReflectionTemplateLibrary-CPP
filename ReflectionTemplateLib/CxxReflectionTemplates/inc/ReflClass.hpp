#pragma once 

#include <cassert>
#include <iostream>

#include "ConstructorReflection.hpp"
#include "ReflClass.h"

namespace rtl {

	template<class _classType>
	class ClassReflection;

	inline const std::string& ReflClass::getClassName() const
	{
		return m_className;
	}

	inline const std::vector<const ReflClass*>& ReflClass::getBaseReflClasses() const
	{
		return m_baseReflTypes;
	}

	inline const unsigned ReflClass::getReflClassId() const
	{
		return m_reflClassId;
	}

	inline const bool ReflClass::isCastSafeToTypeId(const unsigned pTypeId) const
	{
		return (pTypeId == m_reflClassId || m_safeUpCastFunctors.find(pTypeId) != m_safeUpCastFunctors.end());
	}

	inline void ReflClass::initReflectedTypeName(const std::string& pTypenName) const
	{
		m_className = pTypenName;
	}

	inline void ReflClass::initReflectedDestructor(const DctorFunctor pDctorFunctor) const
	{
		m_deleteFunctor = pDctorFunctor;
	}

	inline void ReflClass::initReflectedConstructor(const unsigned pCtorTypeId, const unsigned pCtorIndex) const
	{
		m_ctorFunctorTable.emplace(std::make_pair(pCtorTypeId, pCtorIndex));
	}

	inline const ReflMethod& ReflClass::getMethod(const std::string& pFuncName) const
	{
		//TODO : handle not found exception
		return m_reflFunctions.at(pFuncName);
	}

	template<class _objTy, class..._args>
	inline ReflObject<_objTy> ReflClass::instance(_args...params) const
	{
		return ReflObject<_objTy>(m_reflClassId, construct<_objTy, _args...>(params...), m_deleteFunctor);
	}

	template<ctor _ctorTy, class _objTy>
	inline ReflObject<_objTy> ReflClass::instance(const ReflObject<_objTy>& pSrcObj, 
						      const sfinae_ctorT<_ctorTy, ctor::COPY>* p_null) const
	{
		auto ctor = ctorCOPY();
		return ReflObject<_objTy>(m_reflClassId, construct<_objTy>(pSrcObj.get(), &ctor), m_deleteFunctor);
	}

	template<ctor _ctorTy, class _objTy>
	inline ReflObject<_objTy> ReflClass::instance(const ReflObject<const _objTy>& pSrcObj, 
						      const sfinae_ctorT<_ctorTy, ctor::COPY>* p_null) const
	{
		auto ctor = ctorCOPY();
		return ReflObject<_objTy>(m_reflClassId, construct<_objTy>(const_cast<_objTy*>(pSrcObj.get()), &ctor), m_deleteFunctor);
	}

	template<class _objTy, class..._args>
	inline ReflObject<const _objTy> ReflClass::instanceConst(_args...params) const
	{
		return ReflObject<const _objTy>(m_reflClassId, construct<const _objTy, _args...>(params...), m_deleteFunctor);
	}

	template<ctor _ctorTy, class _objTy>
	inline ReflObject<const _objTy> ReflClass::instanceConst(const ReflObject<_objTy>& pSrcObj, 
								 const sfinae_ctorT<_ctorTy, ctor::COPY>* p_null) const
	{
		auto ctor = ctorCOPY();
		return ReflObject<const _objTy>(m_reflClassId, construct<_objTy>(pSrcObj.get(), &ctor), m_deleteFunctor);
	}

	template<ctor _ctorTy, class _objTy>
	inline ReflObject<const _objTy> ReflClass::instanceConst(const ReflObject<const _objTy>& pSrcObj, 
								 const sfinae_ctorT<_ctorTy, ctor::COPY>* p_null) const
	{
		auto ctor = ctorCOPY();
		return ReflObject<const _objTy>(m_reflClassId, construct<_objTy>(const_cast<_objTy*>(pSrcObj.get()), &ctor), m_deleteFunctor);
	}

	template<class _objTy, class..._args>
	inline _objTy* ReflClass::construct(_args...params) const
	{
		static_assert(!std::is_pointer<_objTy>::value, "newInstance<_objTy>() : template argument \"_objTy\" should not be pointer");

		const unsigned ctorTypeId = ConstructorReflection<void*, _args...>::getConstructorTypeId();
		auto indexItr = m_ctorFunctorTable.find(ctorTypeId);
		const bool isInvocationValid = (indexItr != m_ctorFunctorTable.end());
		assert(isInvocationValid && "Bad constructor call exception.. abort!");

		return static_cast<_objTy*>(ConstructorReflection<void*, _args...>::invoke(m_reflClassId, indexItr->second, params...));
	}

	template<class _classTy, class _baseTy>
	inline void ReflClass::initReflectedInheritance() const
	{
		const bool safeUpCast = 
		ClassReflection<_baseTy>::Instance.m_safeUpCastFunctors.emplace(std::make_pair(m_reflClassId,
		[](void* pTargetObj, const unsigned pTargetTypeId)-> void*
		{
				assert(pTargetTypeId == ClassReflection<_classTy>::Instance.m_reflClassId && "safe static_cast failure.. abort!");
				return static_cast<_baseTy*>(static_cast<_classTy*>(pTargetObj));
		})).second;
		assert(safeUpCast && "static_cast<>() : unsafe up cast error..");
		m_baseReflTypes.push_back(&ClassReflection<_baseTy>::Instance);
	}
}




//std::cout << "\n[up_cast]..\t\t\t{ sc<" << typeid(_baseTy).name() << ">(sc<" << typeid(_classTy).name() << ">(" << pTargetTypeId << ")) }";
