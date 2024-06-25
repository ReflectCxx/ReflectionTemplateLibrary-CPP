
#include<optional>

#include "RObject.hpp"
#include "TestUtilsBook.h"

//User defined types.
#include "Book.h"

using namespace std;
using namespace nsdate;
using namespace rtl::access;

namespace test_utils
{
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
	const bool book::test_new_instance_ctor<>(const std::unique_ptr<rtl::access::RObject>& pInstance)
	{
		optional<Book*> robj = pInstance->get<Book*>();
		if (!robj.has_value()) {
			return false;
		}

		Book book;
		Book& rbook = *(robj.value());
		return (book == rbook);
	}


	template<>
	const bool book::test_new_instance_ctor<double, string>(const std::unique_ptr<rtl::access::RObject>& pInstance)
	{
		optional<Book*> robj = pInstance->get<Book*>();
		if (!robj.has_value()) {
			return false;
		}

		Book book(PRICE, TITLE);
		Book& rbook = *(robj.value());
		return (book == rbook);
	}


	const bool book::test_method_setAuthor(const std::unique_ptr<rtl::access::RObject>& pInstance)
	{
		optional<Book*> robj = pInstance->get<Book*>();
		if (!robj.has_value()) {
			return false;
		}

		Book book;
		Book& rbook = *(robj.value());

		book.setAuthor(AUTHOR);
		return (book == rbook);
	}


	template<>
	const bool book::test_method_updateBookInfo<>(const std::unique_ptr<rtl::access::RObject>& pInstance) 
	{
		optional<Book*> robj = pInstance->get<Book*>();
		if (!robj.has_value()) {
			return false;
		}

		Book book;
		Book& rbook = *(robj.value());

		book.updateBookInfo();
		return (book == rbook);
	}


	template<>
	const bool book::test_method_updateBookInfo<const char*, double, string>(const std::unique_ptr<rtl::access::RObject>& pInstance)
	{
		optional<Book*> robj = pInstance->get<Book*>();
		if (!robj.has_value()) {
			return false;
		}

		Book book;
		Book& rbook = *(robj.value());

		book.updateBookInfo(TITLE, PRICE, string(AUTHOR));
		return (book == rbook);
	}


	template<>
	const bool book::test_method_updateBookInfo<string, double, const char*>(const std::unique_ptr<rtl::access::RObject>& pInstance)
	{
		optional<Book*> robj = pInstance->get<Book*>();
		if (!robj.has_value()) {
			return false;
		}

		Book book;
		Book& rbook = *(robj.value());

		book.updateBookInfo(string(AUTHOR), PRICE, TITLE);
		return (book == rbook);
	}
}