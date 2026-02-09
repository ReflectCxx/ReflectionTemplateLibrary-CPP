

#include "reg_ids.h"
#include "reg_decls.h"

#include "StringWrap.h"


namespace regs8::type0 {
    void init(std::vector<rtl::Function>& fns) {

        fns.push_back(rtl::type().record<StrWrap>(cxx::type::StrWrap::id)
                                 .build());

        fns.push_back(rtl::type().member<StrWrap>()
                                 .constructor<const std::string &>().build());

        fns.push_back(rtl::type().member<StrWrap>()
                                 .methodConst(cxx::type::StrWrap::fn::sstr::id)
                                 .build(&StrWrap::sstr));
    }
}


namespace regs8::type1 {
    void init(std::vector<rtl::Function>& fns) {

        fns.push_back(rtl::type().record<StrWrapA>(cxx::type::StrWrapA::id)
                                 .build());

        fns.push_back(rtl::type().member<StrWrapA>()
                                 .constructor<std::string_view>().build());

        fns.push_back(rtl::type().member<StrWrapA>()
                                 .constructor<std::string &>().build());

        fns.push_back(rtl::type().member<StrWrapA>()
                                 .constructor<const std::string &>().build());

        fns.push_back(rtl::type().member<StrWrapA>()
                                 .constructor<std::string &&>().build());

        fns.push_back(rtl::type().member<StrWrapA>()
                                 .constructor<const char *>().build());
    }
}


namespace regs8::type2 {
    void init(std::vector<rtl::Function>& fns) {

        fns.push_back(rtl::type().record<StrWrapB>(cxx::type::StrWrapB::id)
                                 .build());

        fns.push_back(rtl::type().member<StrWrapB>()
                                 .constructor<const std::string &>().build());

        fns.push_back(rtl::type().member<StrWrapB>()
                                 .constructor<std::string &>().build());
    }
}


namespace regs8::type3 {
    void init(std::vector<rtl::Function>& fns) {

        fns.push_back(rtl::type().record<StrWrapC>(cxx::type::StrWrapC::id)
                                 .build());

        fns.push_back(rtl::type().member<StrWrapC>()
                                 .constructor<std::string &>().build());
    }
}


namespace regs8::type4 {
    void init(std::vector<rtl::Function>& fns) {

        fns.push_back(rtl::type().record<StrWrapD>(cxx::type::StrWrapD::id)
                                 .build());

        fns.push_back(rtl::type().member<StrWrapD>()
                                 .constructor<const std::string &>().build());
    }
}

