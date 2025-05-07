
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


	const bool person::test_method_updateLastName(const std::any& pInstance, bool pOnHeap)
	{
		Person person(FIRST_NAME);
		person.updateLastName(LAST_NAME);

		if (pOnHeap) {
			Person* rPerson = any_cast<Person*>(pInstance);
			if (rPerson == nullptr) {
				return false;
			}
			return (person == *rPerson);
		}
		else {
			auto rPerson = any_cast<Person>(&pInstance);
			return (person == *rPerson);
		}
	}


	const bool person::test_method_updateLastName_const(const std::any& pInstance, bool pOnHeap)
	{
		const Person person(FIRST_NAME);
		person.updateLastName(LAST_NAME);

		if (pOnHeap) {
			//instance created via reflection will always hold non-const pointer only. const(or not) is maintained internally to call appropriate method.
			Person* rPerson = any_cast<Person*>(pInstance);
			if (rPerson == nullptr) {
				return false;
			}
			return (person == *rPerson);
		}
		else {
			auto rPerson = any_cast<Person>(&pInstance);
			return (person == *rPerson);
		}
	}


	const bool person::test_copy_constructor_overload_src_const_obj(const std::any& pInstance, bool pOnHeap)
	{
		const Person personSrc;
		Person person(personSrc);

		if (pOnHeap) {
			//instance created via reflection will always hold non-const pointer only. const(or not) is maintained internally to call appropriate method.
			Person* rPerson = any_cast<Person*>(pInstance);
			if (rPerson == nullptr) {
				return false;
			}
			return (person == *rPerson);
		}
		else {
			auto rPerson = any_cast<Person>(&pInstance);
			return (person == *rPerson);
		}
	}


	const bool person::test_copy_constructor_overload_src_non_const_obj(const std::any& pInstance, bool pOnHeap)
	{
		Person personSrc;
		Person person(personSrc);

		if (pOnHeap) {
			//instance created via reflection will always hold non-const pointer only. const(or not) is maintained internally to call appropriate method.
			Person* rPerson = any_cast<Person*>(pInstance);
			if (rPerson == nullptr) {
				return false;
			}
			return (person == *rPerson);
		}
		else {
			auto rPerson = any_cast<Person>(&pInstance);
			return (person == *rPerson);
		}
	}


	template<>
	const bool person::test_method_updateAddress<string>(const std::any& pInstance, bool pOnHeap)
	{
		Person person(FIRST_NAME);
		person.updateAddress(ADDRESS);

		if (pOnHeap) {
			//instance created via reflection will always hold non-const pointer only. const(or not) is maintained internally to call appropriate method.
			Person* rPerson = any_cast<Person*>(pInstance);
			if (rPerson == nullptr) {
				return false;
			}
			return (person == *rPerson);
		}
		else {
			auto rPerson = any_cast<Person>(&pInstance);
			return (person == *rPerson);
		}
	}


	template<>
	const bool person::test_method_updateAddress_const<string>(const std::any& pInstance, bool pOnHeap)
	{
		const Person person(FIRST_NAME);
		person.updateAddress(ADDRESS);

		if (pOnHeap) {
			//instance created via reflection will always hold non-const pointer only. const(or not) is maintained internally to call appropriate method.
			Person* rPerson = any_cast<Person*>(pInstance);
			if (rPerson == nullptr) {
				return false;
			}
			return (person == *rPerson);
		}
		else {
			auto rPerson = any_cast<Person>(&pInstance);
			return (person == *rPerson);
		}
	}


	template<>
	const bool person::test_method_updateAddress<>(const std::any& pInstance, bool pOnHeap)
	{
		Person person(FIRST_NAME);
		person.updateAddress();

		if (pOnHeap) {
			//instance created via reflection will always hold non-const pointer only. const(or not) is maintained internally to call appropriate method.
			Person* rPerson = any_cast<Person*>(pInstance);
			if (rPerson == nullptr) {
				return false;
			}
			return (person == *rPerson);
		}
		else {
			auto rPerson = any_cast<Person>(&pInstance);
			return (person == *rPerson);
		}
	}


	template<>
	const bool person::test_method_updateAddress_const<>(const std::any& pInstance, bool pOnHeap)
	{
		const Person person(FIRST_NAME);
		person.updateAddress();

		if (pOnHeap) {
			//instance created via reflection will always hold non-const pointer only. const(or not) is maintained internally to call appropriate method.
			Person* rPerson = any_cast<Person*>(pInstance);
			if (rPerson == nullptr) {
				return false;
			}
			return (person == *rPerson);
		}
		else {
			auto rPerson = any_cast<Person>(&pInstance);
			return (person == *rPerson);
		}
	}
}