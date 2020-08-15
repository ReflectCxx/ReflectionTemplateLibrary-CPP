#pragma once

#include "CppMirror.h"
#include "TypeConstants.h"

#include "ClassReflection.hpp"
#include "MethodReflection.hpp"
#include "ReflectionBuilder.hpp"

namespace rtl 
{
	template<class..._args>
	struct args
	{
		template<class _classType, class _retType>
		constexpr static const ReflMethod add(_retType(_classType::* pFunctor)(_args...))
		{
			return ReflMethod::init(pFunctor);
		}
	};
}

namespace rtl 
{
	template<class _classType, class _fieldType>
	inline constexpr void add(_fieldType _classType::* pFieldOffset)
	{
		//TODO : implementation
	}

	template<class _classType, class _retType, class..._args>
	inline constexpr const ReflMethod add(_retType(_classType::* pFunctor)(_args...))
	{
		return ReflMethod::init(pFunctor);
	}

	template<typeQ _funcType, class _classType, class _retType, class..._args>
	inline constexpr const ReflMethod add(_retType(_classType::* pFunctor)(_args...) const,
										  sfinae_typeQT<_funcType, typeQ::CONST>* p_null = nullptr)
	{
		return ReflMethod::init(pFunctor);
	}

	template<typeQ _funcType, class _classType, class _retType, class..._args>
	inline constexpr const ReflMethod add(_retType(_classType::* pFunctor)(_args...),
										  sfinae_typeQT<_funcType, typeQ::STATIC>* p_null = nullptr)
	{
		return ReflMethod::init(pFunctor);
	}
}

namespace rtl 
{
	template<class _classType, class..._args>
	inline constexpr const ClassReflection<_classType>* add(const std::string& pTypeName)
	{
		return &(ReflectionBuilder<_classType, _args...>::build(pTypeName));
	}

	template<class _classType, ctor _ctorTx, class..._args>
	inline constexpr const ClassReflection<_classType>* add(const std::string& pTypeName,
															sfinae_ctorT<_ctorTx, ctor::VOID>* p_null = nullptr)
	{
		return &(ReflectionBuilder<_classType, ctorVOID, _args...>::build(pTypeName));
	}

	template<class _classType, ctor _ctorTx, class..._args>
	inline constexpr const ClassReflection<_classType>* add(const std::string& pTypeName,
															sfinae_ctorT<_ctorTx, ctor::COPY>* p_null = nullptr)
	{
		return &(ReflectionBuilder<_classType, ctorCOPY, _args...>::build(pTypeName));
	}

	template<class _classType, ctor _ctorTx, class..._args>
	inline constexpr const ClassReflection<_classType>* add(const std::string& pTypeName,
															sfinae_ctorT<_ctorTx, ctor::MOVE>* p_null = nullptr)
	{
		return &(ReflectionBuilder<_classType, ctorMOVE, _args...>::build(pTypeName));
	}

	template<class _classType, ctor _ctorTx, ctor _ctorTy, class..._args>
	inline constexpr const ClassReflection<_classType>* add(const std::string& pTypeName,
															sfinae_ctorT<_ctorTx, ctor::VOID>* p_nulla = nullptr, 
															sfinae_ctorT<_ctorTy, ctor::COPY>* p_nullb = nullptr)
	{
		return &(ReflectionBuilder<_classType, ctorVOID, ctorCOPY, _args...>::build(pTypeName));
	}

	template<class _classType, ctor _ctorTx, ctor _ctorTy, class..._args>
	inline constexpr const ClassReflection<_classType>* add(const std::string& pTypeName,
															sfinae_ctorT<_ctorTx, ctor::COPY>* p_nulla = nullptr,
															sfinae_ctorT<_ctorTy, ctor::VOID>* p_nullb = nullptr)
	{
		return &(ReflectionBuilder<_classType, ctorCOPY, ctorVOID, _args...>::build(pTypeName));
	}

	//template<class _classType, ctor _ctorType0, ctor _ctorType1, class..._args>
	//inline const ClassReflection<_classType>& add(const std::string& pTypeName,
	//											  ctor_sfinaeT<_ctorType0, ctor::COPY>* p_nulla = nullptr,
	//											  ctor_sfinaeT<_ctorType1, ctor::MOVE>* p_nullb = nullptr)
	//{
	//	return ReflectionBuilder<_classType, CtorCOPY, CtorMOVE, _args...>::build(pTypeName);
	//}

	//template<class _classType, ctor _ctorType0, ctor _ctorType1, class..._args>
	//inline const ClassReflection<_classType>& add(const std::string& pTypeName,
	//											  ctor_sfinaeT<_ctorType0, ctor::MOVE>* p_nulla = nullptr,
	//											  ctor_sfinaeT<_ctorType1, ctor::COPY>* p_nullb = nullptr)
	//{
	//	return ReflectionBuilder<_classType, CtorCOPY, CtorMOVE, _args...>::build(pTypeName);
	//}

	//template<class _classType, ctor _ctorType0, ctor _ctorType1, class..._args>
	//inline const ClassReflection<_classType>& add(const std::string& pTypeName,
	//											  ctor_sfinaeT<_ctorType0, ctor::VOID>* p_nulla = nullptr,
	//											  ctor_sfinaeT<_ctorType1, ctor::MOVE>* p_nullb = nullptr)
	//{
	//	return ReflectionBuilder<_classType, _args...>::build(pTypeName);
	//}

	//template<class _classType, ctor _ctorType0, ctor _ctorType1, class..._args>
	//inline const ClassReflection<_classType>& add(const std::string& pTypeName,
	//											  ctor_sfinaeT<_ctorType0, ctor::MOVE>* p_nulla = nullptr,
	//											  ctor_sfinaeT<_ctorType1, ctor::VOID>* p_nullb = nullptr)
	//{
	//	return ReflectionBuilder<_classType, _args...>::build(pTypeName);
	//}
}