#pragma once

#include "CxxMirror.hpp"

namespace rtl_tests {

	struct CxxReflection
	{
		using Reflection =  
			rtl::CxxMirror<
			rtl::TypeSignature<>,
			rtl::TypeSignature<const char*, const char*>,
			rtl::TypeSignature<unsigned int>,
			rtl::TypeSignature<float>,
			rtl::TypeSignature<const char*, const char*, unsigned int, float>, 
			rtl::TypeSignature<const char*, std::string, unsigned int, double>,
			std::nullptr_t>;

		static const bool init;

		static Reflection& instance();
	};
}