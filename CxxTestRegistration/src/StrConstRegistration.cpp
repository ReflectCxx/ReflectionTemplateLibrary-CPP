#include <Reflect.hpp>

#include "StringConst.h"
#include "Registration.h"
#include "GlobalTestUtils.h"

using namespace test_utils;

namespace test_mirror
{
    void addTypeIdStringConst(std::unordered_map<std::string, rtl::traits::uid_t>& id)
    {
        id.insert(std::make_pair(StrConst::struct_, rtl::traits::uid<StrConst>::value));
    }

    void registerTypeStringConst(std::vector<rtl::Function>& fns)
	{
        fns.push_back(rtl::type().record<StrConst>(StrConst::struct_)
                                 .build());

        //  Function taking no arguments. '<void>' must be specified if other overload exists else not needed. compiler error otherwise.
        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<void>(str_reverseString)
                                 .build(&StrConst::reverseString));

        //  Overloaded function, takes 'string' arguments. '<string>' must be specified as template parameter.
        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string>(str_reverseString)
                                 .build(&StrConst::reverseString));

        //  Overloaded function, takes 'const char*' arguments.
        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<const char*>(str_reverseString)
                                 .build(&StrConst::reverseString));

        //  numereous other overloads.
 #if defined(__GNUC__) && !defined(__clang__)
        /*
            GCC here fails to automatically resolve the correct overloaded functor
            when both a lvalue reference and an rvalue overload exist.
            To disambiguate, explicitly cast the function pointer, e.g.:

                static_cast<std::string(*)(std::string&&)>(reverseString)
        */
        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string&>(str_reverseString)
                                 .build(static_cast<std::string(StrConst::*)(std::string&) const>(&StrConst::reverseString)));
        
        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<const std::string&>(str_reverseString)
                                 .build(static_cast<std::string(StrConst::*)(const std::string&) const>(&StrConst::reverseString)));
        
        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string&&>(str_reverseString)
                                 .build(static_cast<std::string(StrConst::*)(std::string&&) const>(&StrConst::reverseString)));
#else
        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string&>(str_reverseString)
                                 .build(&StrConst::reverseString));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string&&>(str_reverseString)
                                 .build(&StrConst::reverseString));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<const std::string&>(str_reverseString)
                                 .build(&StrConst::reverseString));
#endif
        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string*>(str_reverseString)
                                 .build(&StrConst::reverseString));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<const std::string*>(str_reverseString)
                                 .build(&StrConst::reverseString));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string_view&>(str_revStrNonConstRefArg)
                                 .build(&StrConst::revStrNonConstRefArg));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string_view&&>(str_revStrRValueRefArg)
                                 .build(&StrConst::revStrRValueRefArg));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<const std::string_view&>(str_revStrConstRefArg)
                                 .build(&StrConst::revStrConstRefArg));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string_view>(str_revStrOverloadValRef)
                                 .build(&StrConst::revStrOverloadValRef));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string_view&>(str_revStrOverloadValRef)
                                 .build(&StrConst::revStrOverloadValRef));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string_view>(str_revStrOverloadValCRef)
                                 .build(&StrConst::revStrOverloadValCRef));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<const std::string_view&>(str_revStrOverloadValCRef)
                                 .build(&StrConst::revStrOverloadValCRef));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string_view&>(str_revStrOverloadValRefAndCRef)
                                 .build(&StrConst::revStrOverloadRefAndCRef));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<const std::string_view&>(str_revStrOverloadValRefAndCRef)
                                 .build(&StrConst::revStrOverloadRefAndCRef));
	}
}