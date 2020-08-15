#pragma once

#include <string>
#include <unordered_map>

namespace rtl 
{
	//Type Qualifier
	enum class typeQ
	{
		CONST,
		MUTABLE,
		STATIC
	};

	//Default Constructor Type
	enum class ctor
	{
		NONE = -1,
		VOID,
		COPY,
		MOVE
	};

	class ReflClass;

	template<class..._args>
	struct ctorArgs {};

	using ReflTypeId = unsigned int;
	using ReflMethodId = unsigned int;
	using FunctorIndex = unsigned int;
	using FunctorTypeId = unsigned int;

	using ctorVOID = ctorArgs<>;
	using ctorCOPY = ctorArgs<std::nullptr_t>;
	using ctorMOVE = ctorArgs<std::nullptr_t, std::nullptr_t>;

	template<class _retTy, class..._args>
	using CtorFunctor = _retTy (*)(_args...);
	using DctorFunctor = void (*)(const void*);
	using InheritanceCastFunctor = void* (*)(void*, const unsigned);
	using ReflectedClassMap = std::unordered_map<std::string, const ReflClass* const>;
	using ReflectedClassIdMap = std::unordered_map<unsigned int, const ReflClass* const>;
	using FunctorTypeIdIndexMap = std::unordered_map<FunctorTypeId, std::pair<ReflMethodId, FunctorIndex>>;

	template<typeQ _funcTx, typeQ _funcTy>
	using sfinae_typeQT = typename std::enable_if<(_funcTx == _funcTy)>::type;

	template<ctor _ctorTx, ctor _ctorTy>
	using sfinae_ctorT = typename std::enable_if<(_ctorTx == _ctorTy)>::type;

	template<ctor _ctorTx, ctor _ctorTy>
	using sfinae_ctorF = typename std::enable_if<(_ctorTx != _ctorTy)>::type;

	template<class _Tx, class _Ty>
	using sfinae_typeT = typename std::enable_if<std::is_same<_Tx, _Ty>::value>::type;

	template<class _Tx, class _Ty>
	using sfinae_typeF = typename std::enable_if<!std::is_same<_Tx, _Ty>::value>::type;

	template<class _baseTy, class _derivedTy>
	using sfinae_baseT = typename std::enable_if<(std::is_base_of<_baseTy, _derivedTy>::value && !std::is_same<_baseTy, _derivedTy>::value)>::type;

	template<class _baseTy, class _derivedTy>
	using sfinae_baseF = typename std::enable_if<!(std::is_base_of<_baseTy, _derivedTy>::value && !std::is_same<_baseTy, _derivedTy>::value)>::type;
}