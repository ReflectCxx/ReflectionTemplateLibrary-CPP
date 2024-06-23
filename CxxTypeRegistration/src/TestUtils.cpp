
#include<optional>

#include "TestUtils.h"
#include "RObject.hpp"

//User defined types.
#include "Date.h"

using namespace std;
using namespace test_project;
using namespace rtl::access;

namespace test_utils 
{
	const bool date::assertZeroInstanceCount()
	{
		return (Date::instanceCount() == 0);
	}

	const bool date::testNewInstanceCtorString(const unique_ptr<RObject>& pInstance)
	{
		optional<Date*> robj = pInstance->get<Date*>();
		if (!robj.has_value()) {
			return false;
		}

		Date dateObj(DATE_STR);
		Date& dateRObj = *(robj.value());

		return (dateObj == dateRObj);
	}

	const bool date::testNewInstanceDefaultCtor(const unique_ptr<RObject>& pInstance)
	{
		optional<Date*> robj = pInstance->get<Date*>();
		if (!robj.has_value()) {
			return false;
		}

		Date dateObj;
		Date& dateRObj = *(robj.value());

		return (dateObj == dateRObj);
	}

	const bool date::testNewInstanceCtorUnsignedInt(const unique_ptr<RObject>& pInstance)
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