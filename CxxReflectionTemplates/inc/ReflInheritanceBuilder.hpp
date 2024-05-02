#pragma once

#include <iostream>

#include "ReflClassBuilder.hpp"
#include "ReflInheritanceBuilder.h"

namespace rtl {

	template<class _typeFamilyList>
	inline ReflInheritanceBuilder<_typeFamilyList>::ReflInheritanceBuilder()
	{
		buildHierarchy();
	}

	template<class _typeFamilyList>
	template<class _typeList>
	inline constexpr static void ReflInheritanceBuilder<_typeFamilyList>::buildHierarchy()
	{
		TypeListIterator<_typeFamilyList>::template linkBaseAndDerivedTypes<_typeList::HEAD>();
		buildHierarchy<_typeList::TAIL>();
	}

	template<class..._args>
	template<class _derivedTy>
	inline constexpr static void TypeListIterator <TypeList<_args...>>::linkBaseAndDerivedTypes(sfinae_baseT<_reflType, _derivedTy>* p_null)
	{
		ReflClassBuilder::buildReflectedInheritance<_derivedTy, _reflType>();
		TypeListIterator<_nextType>::template linkBaseAndDerivedTypes<_derivedTy>();
	}

	template<class..._args>
	template<class _derivedTy>
	inline constexpr static void TypeListIterator <TypeList<_args...>>::linkBaseAndDerivedTypes(sfinae_baseF<_reflType, _derivedTy>* p_null)
	{
		TypeListIterator<_nextType>::template linkBaseAndDerivedTypes<_derivedTy>();
	}
}


//std::cout << "\n\n________________BuildingHierarchy(" << typeid(_typeList::HEAD).name() << ")________________";
//std::cout << "\n" << typeid(_derivedTy).name() << "<-(" << typeid(_reflType).name() << ")";