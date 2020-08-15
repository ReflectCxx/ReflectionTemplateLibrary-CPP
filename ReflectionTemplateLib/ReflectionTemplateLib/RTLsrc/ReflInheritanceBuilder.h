#pragma once

#include "TypeConstants.h"
 
namespace rtl {

	template<class...>
	struct TypeList
	{
		using HEAD = std::nullptr_t;
		using TAIL = std::nullptr_t;
	};

	template<class _arg0, class..._args>
	struct TypeList<_arg0, _args...>
	{
		using HEAD = typename _arg0;
		using TAIL = typename TypeList<_args...>;
	};

	template<class _type>
	struct TypeListIterator;

	template<>
	struct TypeListIterator <TypeList<>>
	{
		template<class _derivedTy>
		constexpr static void linkBaseAndDerivedTypes() { }
		constexpr static void buildHierarchy() { }
	};

	template<class..._args>
	struct TypeListIterator <TypeList<_args...>>
	{
		using _reflType = typename TypeList<_args...>::HEAD;
		using _nextType = typename TypeList<_args...>::TAIL;

		template<class _derivedTy>
		constexpr static void linkBaseAndDerivedTypes(sfinae_baseT<_reflType, _derivedTy>* p_null = nullptr);

		template<class _derivedTy>
		constexpr static void linkBaseAndDerivedTypes(sfinae_baseF<_reflType, _derivedTy>* p_null = nullptr);
	};

	template<class _typeFamilyList>
	struct ReflInheritanceBuilder
	{
		template<class _typeList = _typeFamilyList>
		constexpr static void buildHierarchy();

		template<>
		constexpr static void buildHierarchy<TypeList<>>() { }

		ReflInheritanceBuilder();
	};
}