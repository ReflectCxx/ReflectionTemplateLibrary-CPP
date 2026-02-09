
#include <rtl_builder.h>

#include "StringMute.h"
#include "Registration.h"
#include "GlobalTestUtils.h"

using namespace test_utils;

namespace test_mirror
{
    void Register::typeIdStringMute(std::unordered_map<std::string, rtl::traits::uid_t>& id)
    {
        id.insert(std::make_pair(StrMute::struct_, rtl::traits::uid<StrMute>::value));
    }

	void Register::typeStringMute(std::vector<rtl::Function>& fns)
	{
        fns.push_back(rtl::type().record<StrMute>(StrMute::struct_)
                                 .build());

        //  Function taking no arguments. '<void>' must be specified if other overload exists else not needed. compiler error otherwise.
        fns.push_back(rtl::type().member<StrMute>()
                                 .method<void>(str_reverseString)
                                 .build(&StrMute::reverseString));

        //  Overloaded function, takes 'string' arguments. '<string>' must be specified as template parameter.
        fns.push_back(rtl::type().member<StrMute>()
                                 .method<std::string>(str_reverseString)
                                 .build(&StrMute::reverseString));

        //  Overloaded function, takes 'const char*' arguments.
        fns.push_back(rtl::type().member<StrMute>()
                                 .method<const char*>(str_reverseString)
                                 .build(&StrMute::reverseString));

        //  numereous other overloads.

        /*
            GCC here fails to automatically resolve the correct overloaded functor
            when both a lvalue reference and an rvalue overload exist.
            To disambiguate, explicitly cast the function pointer, e.g.:

                static_cast<std::string(*)(std::string&&)>(reverseString)
        */
        fns.push_back(rtl::type().member<StrMute>()
                                 .method<std::string&>(str_reverseString)
                                 .build(static_cast<std::string(StrMute::*)(std::string&)>(&StrMute::reverseString)));
        
        fns.push_back(rtl::type().member<StrMute>()
                                 .method<const std::string&>(str_reverseString)
                                 .build(static_cast<std::string(StrMute::*)(const std::string&)>(&StrMute::reverseString)));
        
        fns.push_back(rtl::type().member<StrMute>()
                                 .method<std::string&&>(str_reverseString)
                                 .build(static_cast<std::string(StrMute::*)(std::string&&)>(&StrMute::reverseString)));

        fns.push_back(rtl::type().member<StrMute>()
                                 .method<std::string*>(str_reverseString)
                                 .build(&StrMute::reverseString));

        fns.push_back(rtl::type().member<StrMute>()
                                 .method<const std::string*>(str_reverseString)
                                 .build(&StrMute::reverseString));

        fns.push_back(rtl::type().member<StrMute>()
                                 .method<std::string_view&>(str_revStrNonConstRefArg)
                                 .build(&StrMute::revStrNonConstRefArg));

        fns.push_back(rtl::type().member<StrMute>()
                                 .method<std::string_view&&>(str_revStrRValueRefArg)
                                 .build(&StrMute::revStrRValueRefArg));

        fns.push_back(rtl::type().member<StrMute>()
                                 .method<const std::string_view&>(str_revStrConstRefArg)
                                 .build(&StrMute::revStrConstRefArg));

        fns.push_back(rtl::type().member<StrMute>()
                                 .method<std::string_view>(str_revStrOverloadValRef)
                                 .build(&StrMute::revStrOverloadValRef));

        fns.push_back(rtl::type().member<StrMute>()
                                 .method<std::string_view&>(str_revStrOverloadValRef)
                                 .build(&StrMute::revStrOverloadValRef));

        fns.push_back(rtl::type().member<StrMute>()
                                 .method<std::string_view>(str_revStrOverloadValCRef)
                                 .build(&StrMute::revStrOverloadValCRef));

        fns.push_back(rtl::type().member<StrMute>()
                                 .method<const std::string_view&>(str_revStrOverloadValCRef)
                                 .build(&StrMute::revStrOverloadValCRef));

        fns.push_back(rtl::type().member<StrMute>()
                                 .method<std::string_view&>(str_revStrOverloadValRefAndCRef)
                                 .build(&StrMute::revStrOverloadRefAndCRef));

        fns.push_back(rtl::type().member<StrMute>()
                                 .method<const std::string_view&>(str_revStrOverloadValRefAndCRef)
                                 .build(&StrMute::revStrOverloadRefAndCRef));
	}
}