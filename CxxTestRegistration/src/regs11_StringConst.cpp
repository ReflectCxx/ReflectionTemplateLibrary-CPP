

#include "reg_ids.h"
#include "reg_decls.h"

#include "StringConst.h"


namespace regs11::type0 {
    void init(std::vector<rtl::Function>& fns) {

        fns.push_back(rtl::type().record<StrConst>(cxx::type::StrConst::id)
                                 .build());

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string_view>(cxx::type::StrConst::fn::revStrOverloadValCRef::id)
                                 .build(&StrConst::revStrOverloadValCRef));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<const std::string_view &>(cxx::type::StrConst::fn::revStrOverloadValCRef::id)
                                 .build(&StrConst::revStrOverloadValCRef));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<void>(cxx::type::StrConst::fn::reverseString::id)
                                 .build(&StrConst::reverseString));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<const char *>(cxx::type::StrConst::fn::reverseString::id)
                                 .build(&StrConst::reverseString));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string>(cxx::type::StrConst::fn::reverseString::id)
                                 .build(&StrConst::reverseString));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string &>(cxx::type::StrConst::fn::reverseString::id)
                                 .build(&StrConst::reverseString));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string &&>(cxx::type::StrConst::fn::reverseString::id)
                                 .build(&StrConst::reverseString));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<const std::string &>(cxx::type::StrConst::fn::reverseString::id)
                                 .build(&StrConst::reverseString));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string *>(cxx::type::StrConst::fn::reverseString::id)
                                 .build(&StrConst::reverseString));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<const std::string *>(cxx::type::StrConst::fn::reverseString::id)
                                 .build(&StrConst::reverseString));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst(cxx::type::StrConst::fn::revStrConstRefArg::id)
                                 .build(&StrConst::revStrConstRefArg));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst(cxx::type::StrConst::fn::revStrRValueRefArg::id)
                                 .build(&StrConst::revStrRValueRefArg));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst(cxx::type::StrConst::fn::revStrNonConstRefArg::id)
                                 .build(&StrConst::revStrNonConstRefArg));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string_view &>(cxx::type::StrConst::fn::revStrOverloadRefAndCRef::id)
                                 .build(&StrConst::revStrOverloadRefAndCRef));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<const std::string_view &>(cxx::type::StrConst::fn::revStrOverloadRefAndCRef::id)
                                 .build(&StrConst::revStrOverloadRefAndCRef));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string_view>(cxx::type::StrConst::fn::revStrOverloadValRef::id)
                                 .build(&StrConst::revStrOverloadValRef));

        fns.push_back(rtl::type().member<StrConst>()
                                 .methodConst<std::string_view &>(cxx::type::StrConst::fn::revStrOverloadValRef::id)
                                 .build(&StrConst::revStrOverloadValRef));
    }
}

