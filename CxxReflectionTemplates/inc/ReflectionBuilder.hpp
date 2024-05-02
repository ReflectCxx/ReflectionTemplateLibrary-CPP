#pragma once

#include "ReflectionBuilder.h"
#include "ReflClassBuilder.h"
#include "ReflClassBuilder.hpp"

namespace rtl{

	template<class..._args>
	template<class _classTy>
	inline constexpr void ReflectionBuilder<ctorArgs<_args...>>::build()
	{
		ReflClassBuilder::buildConstructor<_classTy, _args...>();
	}

	template<class _arg0, class ..._args>
	template<class _classTy>
	inline constexpr void ReflectionBuilder<_arg0, _args...>::build()
	{
		ReflectionBuilder<_arg0>::template build<_classTy>();
		ReflectionBuilder<_args...>::template build<_classTy>();
	}

	template<class _arg0, class ..._args>
	inline constexpr const ClassReflection<_arg0>& ReflectionBuilder<_arg0, _args...>::build(const std::string& pClassName)
	{
		const ClassReflection<_arg0>&  instance = ReflClassBuilder::buildReflectedInstance<_arg0>(pClassName);
		ReflectionBuilder<_args...>::template build<_arg0>();
		return instance;
	}
}

