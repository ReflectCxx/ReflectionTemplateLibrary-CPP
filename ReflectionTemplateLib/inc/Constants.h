#pragma once

namespace rtl {

	const char* const NS_GLOBAL = "namespace_global";
	const char* const CTOR_SUFFIX = "::ctor::";

#define GETTER(_type, _name, _var)					\
		inline constexpr _type get##_name() const {	\
			return _var;							\
		}
}