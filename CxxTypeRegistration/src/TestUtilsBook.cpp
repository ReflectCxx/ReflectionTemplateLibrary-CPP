
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


	template<>
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

		Book bookObj;
		Book& bookRObj = *(robj.value());

		return (bookObj == bookRObj);
	}


	template<>
	const bool book::test_new_instance_ctor<double, string>(const std::unique_ptr<rtl::access::RObject>& pInstance)
	{
		optional<Book*> robj = pInstance->get<Book*>();
		if (!robj.has_value()) {
			return false;
		}

		Book bookObj(PRICE, TITLE);
		Book& bookRObj = *(robj.value());

		return (bookObj == bookRObj);
	}
}