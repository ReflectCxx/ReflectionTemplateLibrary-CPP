#pragma once

#include "RTLConstants.h"

namespace rtl {

	struct NULLType {
		enum {
			typeIndex = 0
		};
	};
}

namespace rtl {

	template <class H, class T>
	struct ClassTypeList {
		typedef H Head;
		typedef T Tail;
		enum {
			typeIndex = typename Tail::typeIndex + 1
		};
	};
}

namespace rtl {

	template<class...> 
	struct CppTypeReflection;

	template<typename _ctList>
	class TypeListIterator;

	template<> 
	struct CppTypeReflection<> 
	{
		typedef NULLType CTLIST;
	};

	template<class T, class...Ts>
	struct CppTypeReflection<T, Ts...>
	{
		typedef ClassTypeList<T, typename CppTypeReflection<Ts...>::CTLIST> CTLIST;
		typedef TypeListIterator<CTLIST> SYSTEM;
	};
}

