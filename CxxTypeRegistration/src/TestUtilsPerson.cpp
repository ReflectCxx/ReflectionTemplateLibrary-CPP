
#include "TestUtilsPerson.h"

//User defined types.
#include "Person.h"

using namespace std;
namespace test_utils
{
	const bool person::assert_zero_instance_count()
	{
		return (Person::getInstanceCount() == 0);
	}


	const bool person::test_method_updateLastName(const std::any& pInstance)
	{
		Person* rPerson = any_cast<Person*>(pInstance);
		if (rPerson == nullptr) {
			return false;
		}

		Person person(FIRST_NAME);
		person.updateLastName(LAST_NAME);

		return (person == *rPerson);
	}


	const bool person::test_method_updateLastName_const(const std::any& pInstance)
	{
		const Person* rPerson = any_cast<const Person*>(pInstance);
		if (rPerson == nullptr) {
			return false;
		}

		const Person person(FIRST_NAME);
		person.updateLastName(LAST_NAME);

		return (person == *rPerson);
	}


	const bool person::test_method_updateAddress(const std::any& pInstance)
	{
		Person* rPerson = any_cast<Person*>(pInstance);
		if (rPerson == nullptr) {
			return false;
		}

		Person person(FIRST_NAME);
		person.updateAddress(ADDRESS);

		return (person == *rPerson);
	}


	const bool person::test_method_updateAddress_const(const std::any& pInstance)
	{
		const Person* rPerson = any_cast<const Person*>(pInstance);
		if (rPerson == nullptr) {
			return false;
		}

		const Person person(FIRST_NAME);
		person.updateAddress(ADDRESS);

		return (person == *rPerson);
	}
}