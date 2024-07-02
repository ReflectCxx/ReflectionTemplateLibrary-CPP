#pragma once

#include <any>
#include <string>
/*
TestUtils provide the interface to test/compare reflected type objects with actual objects (retrived/created using
strict Types) without exposing the actual type objects to "CxxReflectionTests" project.

Provides interface for Testing/Comparing the class "Book" objects states/returns without exposing the actual type "Book".
*/
namespace test_utils
{
	struct book
	{
		static constexpr const double PRICE = 99.923;
		static constexpr const unsigned int PAGES = 1050;
		static constexpr const char* TITLE = "Somehow, I manage.";
		static constexpr const char* AUTHOR = "Micheal G. Scott";
		static constexpr const char* DESCRIPTION = "World's greatest boss Michael G. Scott, Regional Manager, shares his wisdom with you.";

		static constexpr const char* class_ = "Book";
		static constexpr const char* str_setAuthor = "setAuthor";
		static constexpr const char* str_setDecription = "setDecription";
		static constexpr const char* str_getPublishedOn = "getPublishedOn";
		static constexpr const char* str_setPublishedOn = "setPublishedOn";
		static constexpr const char* str_updateBookInfo = "updateBookInfo";

		static const bool assert_zero_instance_count();

		static const bool test_method_setAuthor(const std::any& pInstance);

		static const bool test_method_getPublishedOn_return(const std::string& pRetStr);

		template<class ..._signature>
		static const bool test_method_updateBookInfo(const std::any& pInstance);

		template<class ..._ctorArgs>
		static const bool test_dynamic_alloc_instance_ctor(const std::any& pInstance);
	};
}