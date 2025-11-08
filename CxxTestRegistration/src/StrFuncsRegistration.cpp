
#include <Reflect.hpp>

#include "StringOps.h"
#include "Registration.h"
#include "GlobalTestUtils.h"

using namespace test_utils;

namespace test_mirror
{
    void registerTypeStringFuncs(std::vector<rtl::Function>& fns)
    {
        //  Function taking no arguments. '<void>' must be specified if other overload exists else not needed. compiler error otherwise.
        fns.push_back(rtl::type().function<void>(str_reverseString)
                                        .build(reverseString));

        //  Overloaded function, takes 'string' arguments. '<string>' must be specified as template parameter.
        fns.push_back(rtl::type().function<std::string>(str_reverseString)
                                        .build(reverseString));

        //  Overloaded function, takes 'const char*' arguments.
        fns.push_back(rtl::type().function<const char*>(str_reverseString)
                                        .build(reverseString));
        //  numereous other overloads.
 #if defined(__GNUC__) && !defined(__clang__)
/*
        GCC here fails to automatically resolve the correct overloaded functor
        when both a lvalue reference and an rvalue overload exist.
        To disambiguate, explicitly cast the function pointer, e.g.:

        static_cast<std::string(*)(std::string&&)>(reverseString)
*/
        fns.push_back(rtl::type().function<std::string&>(str_reverseString)
                                 .build(static_cast<std::string(*)(std::string&)>(reverseString)));
        
        fns.push_back(rtl::type().function<const std::string&>(str_reverseString)
                                 .build(static_cast<std::string(*)(const std::string&)>(reverseString)));
        
        fns.push_back(rtl::type().function<std::string&&>(str_reverseString)
                                 .build(static_cast<std::string(*)(std::string&&)>(reverseString)));
#else
        fns.push_back(rtl::type().function<std::string&>(str_reverseString)
                                 .build(reverseString));

        fns.push_back(rtl::type().function<std::string&&>(str_reverseString)
                                 .build(reverseString));

        fns.push_back(rtl::type().function<const std::string&>(str_reverseString)
                                 .build(reverseString));
#endif
        fns.push_back(rtl::type().function<std::string*>(str_reverseString)
                                 .build(reverseString));

        fns.push_back(rtl::type().function<const std::string*>(str_reverseString)
                                 .build(reverseString));

        fns.push_back(rtl::type().function<std::string_view&>(str_revStrNonConstRefArg)
                                 .build(revStrNonConstRefArg));

        fns.push_back(rtl::type().function<std::string_view&&>(str_revStrRValueRefArg)
                                 .build(revStrRValueRefArg));

        fns.push_back(rtl::type().function<const std::string_view&>(str_revStrConstRefArg)
                                 .build(revStrConstRefArg));

        fns.push_back(rtl::type().function<std::string_view>(str_revStrOverloadValRef)
                                 .build(revStrOverloadValRef));

        fns.push_back(rtl::type().function<std::string_view&>(str_revStrOverloadValRef)
                                 .build(revStrOverloadValRef));

        fns.push_back(rtl::type().function<std::string_view>(str_revStrOverloadValCRef)
                                 .build(revStrOverloadValCRef));

        fns.push_back(rtl::type().function<const std::string_view&>(str_revStrOverloadValCRef)
                                 .build(revStrOverloadValCRef));

        fns.push_back(rtl::type().function<std::string_view&>(str_revStrOverloadValRefAndCRef)
                                 .build(revStrOverloadRefAndCRef));

        fns.push_back(rtl::type().function<const std::string_view&>(str_revStrOverloadValRefAndCRef)
                                 .build(revStrOverloadRefAndCRef));
    }
}