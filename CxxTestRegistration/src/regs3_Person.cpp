

#include "reg_ids.h"
#include "reg_decls.h"

#include "Person.h"


namespace regs3::type0 {
    void init(std::vector<rtl::Function>& fns) {

        fns.push_back(rtl::type().record<Person>(cxx::type::Person::id)
                                 .build());

        fns.push_back(rtl::type().member<Person>()
                                 .constructor<const std::string &>().build());

        fns.push_back(rtl::type().member<Person>()
                                 .methodStatic(cxx::type::Person::fn::getInstanceCount::id)
                                 .build(&Person::getInstanceCount));

        fns.push_back(rtl::type().member<Person>()
                                 .methodStatic(cxx::type::Person::fn::createConst::id)
                                 .build(&Person::createConst));

        fns.push_back(rtl::type().member<Person>()
                                 .method<void>(cxx::type::Person::fn::updateAddress::id)
                                 .build(&Person::updateAddress));

        fns.push_back(rtl::type().member<Person>()
                                 .methodConst<void>(cxx::type::Person::fn::updateAddress::id)
                                 .build(&Person::updateAddress));

        fns.push_back(rtl::type().member<Person>()
                                 .method<std::string>(cxx::type::Person::fn::updateAddress::id)
                                 .build(&Person::updateAddress));

        fns.push_back(rtl::type().member<Person>()
                                 .methodConst<std::string>(cxx::type::Person::fn::updateAddress::id)
                                 .build(&Person::updateAddress));

        fns.push_back(rtl::type().member<Person>()
                                 .methodStatic<void>(cxx::type::Person::fn::getProfile::id)
                                 .build(&Person::getProfile));

        fns.push_back(rtl::type().member<Person>()
                                 .methodStatic<std::string, std::size_t>(cxx::type::Person::fn::getProfile::id)
                                 .build(&Person::getProfile));

        fns.push_back(rtl::type().member<Person>()
                                 .methodStatic<bool>(cxx::type::Person::fn::getProfile::id)
                                 .build(&Person::getProfile));

        fns.push_back(rtl::type().member<Person>()
                                 .method(cxx::type::Person::fn::getFirstName::id)
                                 .build(&Person::getFirstName));

        fns.push_back(rtl::type().member<Person>()
                                 .methodStatic(cxx::type::Person::fn::createPtr::id)
                                 .build(&Person::createPtr));

        fns.push_back(rtl::type().member<Person>()
                                 .methodStatic(cxx::type::Person::fn::getDefaults::id)
                                 .build(&Person::getDefaults));

        fns.push_back(rtl::type().member<Person>()
                                 .methodStatic(cxx::type::Person::fn::deletePtr::id)
                                 .build(&Person::deletePtr));

        fns.push_back(rtl::type().member<Person>()
                                 .methodConst(cxx::type::Person::fn::updateLastName::id)
                                 .build(&Person::updateLastName));
    }
}

