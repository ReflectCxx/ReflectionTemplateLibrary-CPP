
#include<optional>

#include "TestUtilsDate.h"
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
}