
#include<optional>

#include "TestUtils.h"
#include "RObject.hpp"

//User defined types.
#include "Date.h"
#include "Book.h"

using namespace std;
using namespace nsdate;
using namespace rtl::access;

namespace test_utils
{
	const bool date::assert_zero_instance_count()
	{
		return (Date::instanceCount() == 0);
	}

	template<>
	const bool date::test_new_instance_ctor<string>(const unique_ptr<RObject>& pInstance)
	{
		optional<Date*> robj = pInstance->get<Date*>();
		if (!robj.has_value()) {
			return false;
		}

		Date dateObj(DATE_STR);
		Date& dateRObj = *(robj.value());

		return (dateObj == dateRObj);
	}

	template<>
	const bool date::test_new_instance_ctor<>(const unique_ptr<RObject>& pInstance)
	{
		optional<Date*> robj = pInstance->get<Date*>();
		if (!robj.has_value()) {
			return false;
		}

		Date dateObj;
		Date& dateRObj = *(robj.value());

		return (dateObj == dateRObj);
	}

	template<>
	const bool date::test_new_instance_ctor<unsigned, unsigned, unsigned>(const unique_ptr<RObject>& pInstance)
	{
		optional<Date*> robj = pInstance->get<Date*>();
		if (!robj.has_value()) {
			return false;
		}

		Date dateObj(day, month, year);
		Date& dateRObj = *(robj.value());

		return (dateObj == dateRObj);
	}


	const bool book::assert_zero_instance_count()
	{
		return (Book::getInstanceCount() == 0);
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