
#include <rtl_builder.h>

#include "Person.h"
#include "Registration.h"
#include "TestUtilsPerson.h"

using namespace test_utils;

namespace test_mirror
{
    void Register::typeIdPerson(std::unordered_map<std::string, rtl::traits::uid_t>& id)
    {
        id.insert(std::make_pair(person::class_, rtl::traits::uid<Person>::value));
    }

	void Register::typePerson(std::vector<rtl::Function>& fns)
	{
		// class 'Person', methods & constructors.
        fns.push_back(rtl::type().record<Person>(person::class_)
                                 .build());

        fns.push_back(rtl::type().member<Person>()
                                 .constructor<std::string>()
                                 .build());

        fns.push_back(rtl::type().member<Person>()
                                 .methodStatic(person::str_createPtr)
                                 .build(&Person::createPtr));

        fns.push_back(rtl::type().member<Person>()
                                 .method<void>(person::str_updateAddress)
                                 .build(&Person::updateAddress));

        fns.push_back(rtl::type().member<Person>()
                                 .method<std::string>(person::str_updateAddress)
                                 .build(&Person::updateAddress));

        fns.push_back(rtl::type().member<Person>()
                                 .method(person::str_getFirstName)
                                 .build(&Person::getFirstName));

        // Registring const-method, 'methodConst()' function must be used. compiler error otherwise.
        fns.push_back(rtl::type().member<Person>()
                                 .methodConst(person::str_updateLastName)
                                 .build(&Person::updateLastName));

        // Registring const-method overload, non-const overloaded method already registered above.
        fns.push_back(rtl::type().member<Person>()
                                 .methodConst<void>(person::str_updateAddress)
                                 .build(&Person::updateAddress));

        fns.push_back(rtl::type().member<Person>()
                                 .methodConst<std::string>(person::str_updateAddress)
                                 .build(&Person::updateAddress));

        fns.push_back(rtl::type().member<Person>()
                                 .methodStatic(person::str_getDefaults)
                                 .build(&Person::getDefaults));

        fns.push_back(rtl::type().member<Person>()
                                 .methodStatic(person::str_createConst)
                                 .build(&Person::createConst));

        fns.push_back(rtl::type().member<Person>()
                                 .methodStatic<void>(person::str_getProfile)
                                 .build(&Person::getProfile));

        fns.push_back(rtl::type().member<Person>()
                                 .methodStatic<bool>(person::str_getProfile)
                                 .build(&Person::getProfile));

        fns.push_back(rtl::type().member<Person>()
                                 .methodStatic<std::string, size_t>(person::str_getProfile)
                                 .build(&Person::getProfile));
	}
}