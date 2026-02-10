

#include "reg_ids.h"
#include "reg_decls.h"

#include "StringStatic.h"


namespace regs5::type0 {
    void init(std::vector<rtl::Function>& fns) {

        fns.push_back(rtl::type().record<StrStatic>(cxx::type::StrStatic::id)
                                 .build());

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string_view>(cxx::type::StrStatic::fn::revStrOverloadValCRef::id)
                                 .build(&StrStatic::revStrOverloadValCRef));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<const std::string_view &>(cxx::type::StrStatic::fn::revStrOverloadValCRef::id)
                                 .build(&StrStatic::revStrOverloadValCRef));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<void>(cxx::type::StrStatic::fn::reverseString::id)
                                 .build(&StrStatic::reverseString));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<const char *>(cxx::type::StrStatic::fn::reverseString::id)
                                 .build(&StrStatic::reverseString));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string>(cxx::type::StrStatic::fn::reverseString::id)
                                 .build(&StrStatic::reverseString));

    /*  GCC here fails to automatically resolve the correct overloaded functor
        when both a lvalue reference and an rvalue overload exist.
        To disambiguate, explicitly cast the member function pointer.
    */  fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string &>(cxx::type::StrStatic::fn::reverseString::id)
                                 .build(static_cast<std::string(*)(std::string&)>(&StrStatic::reverseString)));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string &&>(cxx::type::StrStatic::fn::reverseString::id)
                                 .build(static_cast<std::string(*)(std::string&&)>(&StrStatic::reverseString)));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<const std::string &>(cxx::type::StrStatic::fn::reverseString::id)
                                 .build(static_cast<std::string(*)(const std::string&)>(&StrStatic::reverseString)));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string *>(cxx::type::StrStatic::fn::reverseString::id)
                                 .build(&StrStatic::reverseString));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<const std::string *>(cxx::type::StrStatic::fn::reverseString::id)
                                 .build(&StrStatic::reverseString));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic(cxx::type::StrStatic::fn::revStrConstRefArg::id)
                                 .build(&StrStatic::revStrConstRefArg));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic(cxx::type::StrStatic::fn::revStrRValueRefArg::id)
                                 .build(&StrStatic::revStrRValueRefArg));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic(cxx::type::StrStatic::fn::revStrNonConstRefArg::id)
                                 .build(&StrStatic::revStrNonConstRefArg));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string_view &>(cxx::type::StrStatic::fn::revStrOverloadRefAndCRef::id)
                                 .build(&StrStatic::revStrOverloadRefAndCRef));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<const std::string_view &>(cxx::type::StrStatic::fn::revStrOverloadRefAndCRef::id)
                                 .build(&StrStatic::revStrOverloadRefAndCRef));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string_view>(cxx::type::StrStatic::fn::revStrOverloadValRef::id)
                                 .build(&StrStatic::revStrOverloadValRef));

        fns.push_back(rtl::type().member<StrStatic>()
                                 .methodStatic<std::string_view &>(cxx::type::StrStatic::fn::revStrOverloadValRef::id)
                                 .build(&StrStatic::revStrOverloadValRef));
    }
}

