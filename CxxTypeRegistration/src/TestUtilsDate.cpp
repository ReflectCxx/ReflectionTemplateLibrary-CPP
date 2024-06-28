
#include "TestUtilsDate.h"
#include "TestUtilsGlobals.h"

//User defined types.
#include "Date.h"

using namespace std;
using namespace nsdate;
using namespace rtl::access;

namespace test_utils
{
	const bool date::assert_zero_instance_count()
	{
		//Fix Me: enable destructor reflection
		return true;// (Date::instanceCount() == 0);
	}


	template<>
	const bool date::test_new_instance_ctor<>(const Rany& pInstance)
	{
		Date* rdate = test_utils::getObject<Date*>(pInstance);
		if (rdate == nullptr) {
			return false;
		}
		return (Date() == *rdate);
	}


	template<>
	const bool date::test_new_instance_ctor<string>(const Rany& pInstance)
	{
		Date* rdate = test_utils::getObject<Date*>(pInstance);
		if (rdate == nullptr) {
			return false;
		}
		return (Date(DATE_STR) == *rdate);
	}


	template<>
	const bool date::test_new_instance_ctor<unsigned, unsigned, unsigned>(const Rany& pInstance)
	{
		Date* rdate = test_utils::getObject<Date*>(pInstance);
		if (rdate == nullptr) {
			return false;
		}
		return (Date(day, month, year) == *rdate);
	}
}