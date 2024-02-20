#pragma once

#include <string>

namespace rtl {

	template<class..._args>
	struct ctorArgs;

	template<class ..._args>
	struct ReflectionBuilder;

	template<>
	struct ReflectionBuilder<>
	{
		template<class _classTy>
		constexpr static void build() {}
	};

	template<class..._args>
	struct ReflectionBuilder<ctorArgs<_args...>> 
	{
		template<class _classTy>
		constexpr static void build();
	};

	template<class _arg0, class ..._args>
	struct ReflectionBuilder<_arg0, _args...> 
	{
		constexpr static const ClassReflection<_arg0>& build(const std::string& pClassName);

		template<class _classTy>
		constexpr static void build();
	};
}
