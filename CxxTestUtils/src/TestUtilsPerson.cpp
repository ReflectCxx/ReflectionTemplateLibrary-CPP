
#include "TestUtilsPerson.h"

#include <rtl/inc/RObject.hpp>

//User defined types.
#include "Person.h"

using namespace std;
namespace test_utils
{
	const bool person::assert_zero_instance_count()
	{
		return (Person::getInstanceCount() == 0);
	}


	const string person::get_str_returned_on_call_getDefaults() 
	{
		return Person::getDefaults();
	}


	template<>
	const std::string person::get_str_returned_on_call_getProfile(const bool pNoAddress)
	{
		return Person::getProfile();
	}


	template<>
	const std::string person::get_str_returned_on_call_getProfile<bool>(const bool pNoAddress)
	{
		return Person::getProfile(pNoAddress);
	}


	template<>
	const std::string person::get_str_returned_on_call_getProfile<string, size_t>(const bool pNoAddress)
	{
		return Person::getProfile(OCCUPATION, AGE);
	}


	const bool person::test_method_updateLastName_const(const rtl::RObject& pInstance)
	{
		if (pInstance.canViewAs<Person>()) 
		{
			const Person person(FIRST_NAME);
			person.updateLastName(LAST_NAME);
			const Person& rPerson = pInstance.view<Person>()->get();
			return (person == rPerson);
		}
		return false;

	}


	template<>
	const bool person::test_method_updateAddress<string>(const rtl::RObject& pInstance)
	{
		if (pInstance.canViewAs<Person>()) 
		{
			Person person(FIRST_NAME);
			person.updateAddress(ADDRESS);
			const Person& rPerson = pInstance.view<Person>()->get();
			return (person == rPerson);
		}
		return false;
	}


	const bool person::delete_unmanaged_person_instance_created_via_createPtr(const rtl::RObject& pInstance)
	{
		if (pInstance.canViewAs<Person>()) 
		{
			const Person& rPerson = pInstance.view<Person>()->get();
			Person::deletePtr(&rPerson);
			return true;
		}
		return false;
	}


	template<>
	const bool person::test_method_updateAddress_const<string>(const rtl::RObject& pInstance)
	{
		if (pInstance.canViewAs<Person>()) 
		{
			const Person person(FIRST_NAME);
			person.updateAddress(ADDRESS);
			const Person& rPerson = pInstance.view<Person>()->get();
			return (person == rPerson);
		}
		return false;
	}


	template<>
	const bool person::test_method_updateAddress<>(const rtl::RObject& pInstance)
	{
		if (pInstance.canViewAs<Person>()) 
		{
			Person person(FIRST_NAME);
			person.updateAddress();
			const Person& rPerson = pInstance.view<Person>()->get();
			return (person == rPerson);
		}
		return false;
	}


	template<>
	const bool person::test_method_updateAddress_const<>(const rtl::RObject& pInstance)
	{
		if (pInstance.canViewAs<Person>()) 
		{
			const Person person(FIRST_NAME);
			person.updateAddress();
			const Person& rPerson = pInstance.view<Person>()->get();
			return (person == rPerson);
		}
		return false;
	}
}