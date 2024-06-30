
#include "TestUtilsDate.h"
#include "TestUtilsGlobals.h"

//User defined types.
#include "Date.h"

using namespace std;
using namespace nsdate;

namespace test_utils
{
	const bool date::assert_zero_instance_count()
	{
		return (Date::instanceCount() == 0);
	}


	template<>
	const bool date::test_static_alloc_instance_ctor<>(const any& pInstance)
	{
		return (Date() == any_cast<Date>(pInstance));
	}


	template<>
	const bool date::test_static_alloc_instance_ctor<string>(const any& pInstance)
	{
		return (Date(DATE_STR) == any_cast<Date>(pInstance));
	}


	template<>
	const bool date::test_static_alloc_instance_ctor<unsigned, unsigned, unsigned>(const any& pInstance)
	{
		return (Date(day, month, year) == any_cast<Date>(pInstance));
	}


	template<>
	const bool date::test_dynamic_alloc_instance_ctor<>(const any& pInstance)
	{
		Date* rdate = any_cast<Date*>(pInstance);
		if (rdate == nullptr) {
			return false;
		}
		return (Date() == *rdate);
	}


	template<>
	const bool date::test_dynamic_alloc_instance_ctor<string>(const any& pInstance)
	{
		Date* rdate = any_cast<Date*>(pInstance);
		if (rdate == nullptr) {
			return false;
		}
		return (Date(DATE_STR) == *rdate);
	}


	template<>
	const bool date::test_dynamic_alloc_instance_ctor<unsigned, unsigned, unsigned>(const any& pInstance)
	{
		Date* rdate = any_cast<Date*>(pInstance);
		if (rdate == nullptr) {
			return false;
		}
		return (Date(day, month, year) == *rdate);
	}
}