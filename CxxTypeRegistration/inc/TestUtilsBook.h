#pragma once

#include <memory>

#include "RObject.h"

namespace test_utils
{
	struct book 
	{
		static constexpr const double PRICE = 99.923;
		static constexpr const unsigned int PAGES = 1050;
		static constexpr const char* TITLE = "Somehow, I manage.";
		static constexpr const char* AUTHOR = "Micheal G. Scott";

		static const bool assert_zero_instance_count();

		template<class ..._ctorArgs>
		static const bool test_new_instance_ctor(const std::unique_ptr<rtl::access::RObject>& pInstance);

		template<class ..._ctorArgs>
		static const bool test_method_getPublishedOn_return(const std::string& pRetStr);
	};
}