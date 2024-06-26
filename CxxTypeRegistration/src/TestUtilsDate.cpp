
#include<optional>

#include "TestUtilsDate.h"
#include "TestUtilsGlobals.h"
#include "RObject.hpp"

//User defined types.
#include "Date.h"

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
	const bool date::test_new_instance_ctor<>(const unique_ptr<RObject>& pInstance)
	{
		Date* rdate = test_utils::getObject<Date>(pInstance);
		if (rdate == nullptr) {
			return false;
		}
		return (Date() == *rdate);
	}


	template<>
	const bool date::test_new_instance_ctor<string>(const unique_ptr<RObject>& pInstance)
	{
		Date* rdate = test_utils::getObject<Date>(pInstance);
		if (rdate == nullptr) {
			return false;
		}
		return (Date(DATE_STR) == *rdate);
	}


	template<>
	const bool date::test_new_instance_ctor<unsigned, unsigned, unsigned>(const unique_ptr<RObject>& pInstance)
	{
		Date* rdate = test_utils::getObject<Date>(pInstance);
		if (rdate == nullptr) {
			return false;
		}
		return (Date(day, month, year) == *rdate);
	}
}