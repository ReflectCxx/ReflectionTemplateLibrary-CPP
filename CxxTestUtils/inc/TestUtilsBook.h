#pragma once
/*
TestUtils provide the interface to test/compare reflected type objects with actual objects (retrived/created using
strict Types) without exposing the actual type objects to "CxxReflectionTests" project.

Provides interface for Testing/Comparing the class "Book" objects states/returns without exposing the actual type "Book".
*/

#include <string>

namespace rtl {
	class RObject;
}

namespace test_utils
{
	struct library
	{
		static constexpr const char* class_ = "Library";
		static constexpr const char* str_addBook = "addBook";
		static constexpr const char* str_getBookByTitle = "getBookByTitle";

		static const bool assert_zero_instance_count();
	};

	struct book
	{
		static constexpr const double PRICE = 99.923;
		static constexpr const char* TITLE = "Somehow, I manage.";
		static constexpr const char* AUTHOR = "Micheal G. Scott";
		static constexpr const char* DESCRIPTION = "World's greatest boss Michael G. Scott, Regional Manager, shares his wisdom with you.";
		static constexpr const char* COPYRIGHT_TAG = "Copyright (c) Micheal Scott Paper Company Pvt. Ltd.";
		static constexpr const char* PREFACE = "This is a preface.";
		static constexpr const char* ACKNOWLEDGEMENTS = "This is an acknowledgement.";

		static constexpr const char* class_ = "Book";
		static constexpr const char* str_setAuthor = "setAuthor";
		static constexpr const char* str_addPreface = "addPreface";
		static constexpr const char* str_setDescription = "setDescription";
		static constexpr const char* str_getPublishedOn = "getPublishedOn";
		static constexpr const char* str_setPublishedOn = "setPublishedOn";
		static constexpr const char* str_updateBookInfo = "updateBookInfo";
		static constexpr const char* str_addCopyrightTag = "addCopyrightTag";

		static const int get_book_instance_count();

		static const bool assert_zero_instance_count();

		static const bool test_method_setAuthor(const rtl::RObject& pInstance);

		static const bool test_method_addPreface(const rtl::RObject& pInstance);

		static const bool test_method_addCopyrightTag(const rtl::RObject& pInstance);

		static const bool test_method_getPublishedOn_return(const std::string& pRetStr);

		template<class ..._signature>
		static const bool test_method_updateBookInfo(const rtl::RObject& pInstance);

		template<class ..._ctorArgs>
		static const bool test_dynamic_alloc_instance_ctor(const rtl::RObject& pInstance);

		static const bool test_copy_ctor_with_mutated_object(const rtl::RObject& pInstance);
	};
}