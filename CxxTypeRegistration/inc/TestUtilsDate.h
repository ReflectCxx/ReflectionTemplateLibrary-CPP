#pragma once

#include <memory>

#include "RObject.h"

namespace test_utils
{
	struct date
	{
		static constexpr const unsigned day = 1;
		static constexpr const unsigned month = 1;
		static constexpr const unsigned year = 2000;
		static constexpr const char* ns = "nsdate";
		static constexpr const char* struct_ = "Date";
		static constexpr const char* DATE_STR = "23/12/2024";
		
		static const bool assert_zero_instance_count();

		template<class ..._argsType>
		static const bool test_new_instance_ctor(const std::unique_ptr<rtl::access::RObject>& pInstance);
	};
}