
#include <Reflect.hpp>

#include "Registration.h"

namespace test_mirror
{
    void addTypeIdPodStd(std::unordered_map<std::string, std::size_t>& id)
    {
        id.insert(std::make_pair("int", rtl::detail::TypeId<int>::get()));
        id.insert(std::make_pair("char", rtl::detail::TypeId<char>::get()));
        id.insert(std::make_pair("string", rtl::detail::TypeId<std::string>::get()));
        id.insert(std::make_pair("string_view", rtl::detail::TypeId<std::string_view>::get()));
    }

	void registerPodStdTypes(std::vector<rtl::Function>& fns)
	{
        //  Registering int.
        fns.push_back(rtl::type().record<int>("int")
                                 .build());

        //  Registering type 'int' again, ignored & emits-
        //  [WARNING] Multiple registrations of the same type detected.
        fns.push_back(rtl::type().record<int>("int")
                                 .build());

        //  Registering type 'void' again, but with different name. ignored & emits-
        //  [WARNING] Multiple registrations of the same type detected.
        fns.push_back(rtl::type().record<int>("ccint")
                                 .build());

        //  Registering pod, reflecting- constructor, copy-constructor & destructor.
        fns.push_back(rtl::type().record<char>("char")
                                 .build());

        fns.push_back(rtl::type().ns("std")
                                 .record<std::string_view>("string_view")
                                 .build());

        //  Registers std::string class
        fns.push_back(rtl::type().member<std::string>()
                                 .methodConst("empty")
                                 .build(&std::string::empty));

    /*  Attempting to register the same type(`std::string`) again under a different name.
    *   RTL will ignore this duplicate registration and retain the first one. Emits a warning on the console:
    *   "[WARNING] Multiple registrations of the same type with different names detected."
    */  fns.push_back(rtl::type().member<std::string>()
                                 .methodConst("empty")
                                 .build(&std::string::empty));

        fns.push_back(rtl::type().ns("std")
                                 .record<std::string>("string")
                                 .build());

        fns.push_back(rtl::type().member<std::string>()
                                 .constructor<const char*>()
                                 .build());

    /*  Attempting to register std::string_view, but the provided member function pointer belongs to std::string.
    *   RTL will ignore this registration. Emits a warning on the console:
    *   "[WARNING] Member function pointer does not belong to the class being registered!"
    */  fns.push_back(rtl::type().member<std::string_view>()
                                 .methodConst("empty")
                                 .build(&std::string::empty));

        //  Finally, register std::string_view with correct member-function-pointer
        fns.push_back(rtl::type().member<std::string_view>()
                                 .methodConst("empty")
                                 .build(&std::string_view::empty));
	}
}