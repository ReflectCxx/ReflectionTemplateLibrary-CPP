
#include "TestUtilsDate.h"

//User defined types.
#include "Date.h"

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

	const bool date::test_if_obejcts_are_equal(const std::any& pInstance0, const std::any& pInstance1, bool pCastAsPtr)
	{
		if (pCastAsPtr) {
			auto rdate0 = any_cast<const Date*>(pInstance0);
			auto rdate1 = any_cast<const Date*>(pInstance1);
			return (*rdate0 == *rdate1);
		}
		else {
			auto rdate0 = any_cast<Date>(&pInstance0);
			auto rdate1 = any_cast<Date>(&pInstance1);
			return (*rdate0 == *rdate1);
		}
	}


	template<>
	const bool date::test_dynamic_alloc_instance_ctor<>(const any& pInstance, bool pCastAsPtr)
	{
		if (pCastAsPtr) {
			const Date* rdate = any_cast<const Date*>(pInstance);
			if (rdate == nullptr) {
				return false;
			}
			return (Date() == *rdate);
		}
		else {
			auto rdate = any_cast<Date>(&pInstance);
			return (Date() == *rdate);
		}
	}


	template<>
	const bool date::test_dynamic_alloc_instance_ctor<string>(const any& pInstance, bool pCastAsPtr)
	{
		if (pCastAsPtr) {
			const Date* rdate = any_cast<const Date*>(pInstance);
			if (rdate == nullptr) {
				return false;
			}
			return (Date(DATE_STR0) == *rdate);
		}
		else {
			auto rdate = any_cast<Date>(&pInstance);
			return (Date(DATE_STR0) == *rdate);
		}
	}


	template<>
	const bool date::test_dynamic_alloc_instance_ctor<unsigned, unsigned, unsigned>(const any& pInstance, bool pCastAsPtr)
	{
		if (pCastAsPtr) {
			const Date* rdate = any_cast<const Date*>(pInstance);
			if (rdate == nullptr) {
				return false;
			}
			return (Date(DAY, MONTH, YEAR) == *rdate);
		}
		else {
			auto rdate = any_cast<Date>(&pInstance);
			return (Date(DAY, MONTH, YEAR) == *rdate);
		}
		
	}
}