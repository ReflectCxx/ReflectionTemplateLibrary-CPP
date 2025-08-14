
#include "TestUtilsBook.h"

#include "RObject.hpp"

//User defined types.
#include "Book.h"
#include "Library.h"

using namespace std;
using namespace nsdate;

namespace test_utils
{
	const bool library::assert_zero_instance_count()
	{
		return (Library::getInstanceCount() == 0);
	}

	const int book::get_book_instance_count()
	{
		return Book::getInstanceCount();
	}

	const bool book::assert_zero_instance_count()
	{
		return (Book::getInstanceCount() == 0);
	}


	const bool book::test_method_getPublishedOn_return(const std::string& pRetStr)
	{
		Book bookObj;
		return (bookObj.getPublishedOn() == pRetStr);
	}


	template<>
	const bool book::test_dynamic_alloc_instance_ctor<>(const rtl::access::RObject& pInstance)
	{
		if (pInstance.canViewAs<Book>()) 
		{
			const auto& rbook = pInstance.view<Book>()->get();
			return (Book() == rbook);
		}
		return false;
	}


	template<>
	const bool book::test_dynamic_alloc_instance_ctor<double, string>(const rtl::access::RObject& pInstance)
	{
		if (pInstance.canViewAs<Book>())
		{
			const auto& rbook = pInstance.view<Book>()->get();
			return (Book(PRICE, TITLE) == rbook);
		}
		return false;
	}


	const bool book::test_method_setAuthor(const rtl::access::RObject& pInstance)
	{
		if (pInstance.canViewAs<Book>())
		{
			Book book;
			book.setAuthor(AUTHOR);
			const auto& rbook = pInstance.view<Book>()->get();
			return (book == rbook);
		}
		return false;
	}

	const bool book::test_method_addCopyrightTag(const rtl::access::RObject& pInstance)
	{
		if (pInstance.canViewAs<Book>())
		{
			Book book;
			book.addCopyrightTag(COPYRIGHT_TAG);
			const auto& rbook = pInstance.view<Book>()->get();
			return (book == rbook);
		}
		return false;
	}


	const bool book::test_method_addPreface(const rtl::access::RObject& pInstance)
	{
		if (pInstance.canViewAs<Book>())
		{
			Book book;
			book.addPreface(ACKNOWLEDGEMENTS, PREFACE);
			const auto& rbook = pInstance.view<Book>()->get();
			return (book == rbook);
		}
		return false;
	}


	template<>
	const bool book::test_method_updateBookInfo<>(const rtl::access::RObject& pInstance)
	{
		if (pInstance.canViewAs<Book>())
		{
			Book book;
			book.updateBookInfo();
			const auto& rbook = pInstance.view<Book>()->get();
			return (book == rbook);
		}
		return false;
	}


	template<>
	const bool book::test_method_updateBookInfo<const char*, double, string>(const rtl::access::RObject& pInstance)
	{
		if (pInstance.canViewAs<Book>())
		{
			Book book;
			book.updateBookInfo(TITLE, PRICE, string(AUTHOR));
			const auto& rbook = pInstance.view<Book>()->get();
			return (book == rbook);
		}
		return false;
	}


	template<>
	const bool book::test_method_updateBookInfo<string, double, const char*>(const rtl::access::RObject& pInstance)
	{
		if (pInstance.canViewAs<Book>())
		{
			Book book;
			book.updateBookInfo(string(AUTHOR), PRICE, TITLE);
			const auto& rbook = pInstance.view<Book>()->get();
			return (book == rbook);
		}
		return false;
	}


	const bool test_utils::book::test_copy_ctor_with_mutated_object(const rtl::access::RObject& pInstance)
	{
		if (pInstance.canViewAs<Book>())
		{
			Book obj(PRICE, TITLE);
			obj.setAuthor(AUTHOR);
			obj.setDescription(DESCRIPTION);
			Book copyObj(obj);
			const auto& rbook = pInstance.view<Book>()->get();
			return (copyObj == rbook);
		}
		return false;
	}
}