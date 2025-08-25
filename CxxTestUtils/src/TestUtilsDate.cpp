
#include "RObject.hpp"

//User defined types.
#include "Date.h"
#include "TestUtilsDate.h"

using namespace std;
using namespace nsdate;

namespace test_utils
{
	const bool calender::assert_zero_instance_count()
	{
		return (Calender::instanceCount() == 0);
	}

	const std::size_t calender::get_instance_count()
	{
		return Calender::instanceCount();
	}

	const bool event::assert_zero_instance_count()
	{
		return (Event::instanceCount() == 0);
	}

	const std::size_t event::get_instance_count()
	{
		return Event::instanceCount();
	}

	const std::size_t date::get_instance_count()
	{
		return Date::instanceCount();
	}

	const bool date::test_if_obejcts_are_equal(const rtl::RObject& pInstance0, const rtl::RObject& pInstance1)
	{
		if (pInstance0.canViewAs<Date>() && pInstance1.canViewAs<Date>()) 
		{
			const Date& rdate0 = pInstance0.view<Date>()->get();
			const Date& rdate1 = pInstance1.view<Date>()->get();
			return (rdate0 == rdate1);
		}
		return false;
	}

	template<>
	const bool date::test_dynamic_alloc_instance_ctor<>(const rtl::RObject& pInstance)
	{
		if (pInstance.canViewAs<Date>()) {
			const Date& rdate = pInstance.view<Date>()->get();
			return (Date() == rdate);
		}
		return false;
	}

	template<>
	const bool date::test_dynamic_alloc_instance_ctor<string>(const rtl::RObject& pInstance)
	{
		if (pInstance.canViewAs<Date>()) {
			const Date& rdate = pInstance.view<Date>()->get();
			return (Date(DATE_STR0) == rdate);
		}
		return false;
	}


	template<>
	const bool date::test_dynamic_alloc_instance_ctor<unsigned, unsigned, unsigned>(const rtl::RObject& pInstance)
	{
		if (pInstance.canViewAs<Date>()) {
			const Date& rdate = pInstance.view<Date>()->get();
			return (Date(DAY, MONTH, YEAR) == rdate);
		}
		return false;
	}
}