#pragma once

#include <memory>
#include <optional>

namespace test_utils {

	extern const char* REV_STR_VOID_RET;

	static constexpr double g_real = 3.92;
	static constexpr double g_imaginary = 9.27;

	static constexpr const char* STRA = "ReflectC++";
	static constexpr const char* STRA_REVERSE = "++CtcelfeR";

	static constexpr const char* STRB = "cxxReflection";
	static constexpr const char* STRB_REVERSE = "noitcelfeRxxc";

	static constexpr const char* str_reverseString = "reverseString";
	static constexpr const char* str_getComplexNumAsString = "getComplexNumAsString";

	static constexpr const char* str_complex = "complex";
	static constexpr const char* str_setReal = "setReal";
	static constexpr const char* str_setImaginary = "setImaginary";
	static constexpr const char* str_getMagnitude = "getMagnitude";

	template<class Type>
	static Type* getObject(const std::unique_ptr<rtl::access::RObject>& pInstance)
	{
		std::optional<Type*> robj = pInstance->get<Type*>();
		if (!robj.has_value()) {
			return nullptr;
		}
		return robj.value();
	}
}