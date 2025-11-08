#include <Reflect.hpp>

#include "StringOps.h"
#include "Registration.h"
#include "GlobalTestUtils.h"

using namespace test_utils;

namespace test_mirror
{
    void addTypeIdStringStatic(std::unordered_map<std::string, std::size_t>& id)
    {
        id.insert(std::make_pair(StrStatic::struct_, rtl::detail::TypeId<StrStatic>::get()));
    }

    void registerTypeStringStatic(std::vector<rtl::Function>& fns)
	{
        fns.push_back(rtl::type().record<StrStatic>(StrStatic::struct_)
                                 .build());

        //  Function taking no arguments. '<void>' must be specified if other overload exists else not needed. compiler error otherwise.
        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<void>(str_reverseString)
                                 .build(&StrStatic::reverseString));

        //  Overloaded function, takes 'string' arguments. '<string>' must be specified as template parameter.
        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string>(str_reverseString)
                                 .build(&StrStatic::reverseString));

        //  Overloaded function, takes 'const char*' arguments.
        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<const char*>(str_reverseString)
                                 .build(&StrStatic::reverseString));

        //  numereous other overloads.
 #if defined(__GNUC__) && !defined(__clang__)
        /*
            GCC here fails to automatically resolve the correct overloaded functor
            when both a lvalue reference and an rvalue overload exist.
            To disambiguate, explicitly cast the function pointer, e.g.:

                static_cast<std::string(*)(std::string&&)>(reverseString)
        */
        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string&>(str_reverseString)
                                 .build(static_cast<std::string(StrStatic::*)(std::string&)>(&StrStatic::reverseString)));
        
        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<const std::string&>(str_reverseString)
                                 .build(static_cast<std::string(StrStatic::*)(const std::string&)>(&StrStatic::reverseString)));
        
        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string&&>(str_reverseString)
                                 .build(static_cast<std::string(StrStatic::*)(std::string&&)>(&StrStatic::reverseString)));
#else
        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string&>(str_reverseString)
                                 .build(&StrStatic::reverseString));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string&&>(str_reverseString)
                                 .build(&StrStatic::reverseString));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<const std::string&>(str_reverseString)
                                 .build(&StrStatic::reverseString));
#endif
        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string*>(str_reverseString)
                                 .build(&StrStatic::reverseString));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<const std::string*>(str_reverseString)
                                 .build(&StrStatic::reverseString));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string_view&>(str_revStrNonConstRefArg)
                                 .build(&StrStatic::revStrNonConstRefArg));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string_view&&>(str_revStrRValueRefArg)
                                 .build(&StrStatic::revStrRValueRefArg));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<const std::string_view&>(str_revStrConstRefArg)
                                 .build(&StrStatic::revStrConstRefArg));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string_view>(str_revStrOverloadValRef)
                                 .build(&StrStatic::revStrOverloadValRef));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string_view&>(str_revStrOverloadValRef)
                                 .build(&StrStatic::revStrOverloadValRef));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string_view>(str_revStrOverloadValCRef)
                                 .build(&StrStatic::revStrOverloadValCRef));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<const std::string_view&>(str_revStrOverloadValCRef)
                                 .build(&StrStatic::revStrOverloadValCRef));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string_view&>(str_revStrOverloadValRefAndCRef)
                                 .build(&StrStatic::revStrOverloadRefAndCRef));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<const std::string_view&>(str_revStrOverloadValRefAndCRef)
                                 .build(&StrStatic::revStrOverloadRefAndCRef));
	}
}