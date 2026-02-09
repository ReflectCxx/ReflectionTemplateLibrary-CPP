

#include "reg_ids.h"
#include "reg_decls.h"

#include "StringOps.h"


namespace regs7::fn {
    void init(std::vector<rtl::Function>& fns) {

        fns.push_back(rtl::type().function<std::string_view>(cxx::fn::revStrOverloadValCRef::id)
                                 .build(&revStrOverloadValCRef));

        fns.push_back(rtl::type().function<const std::string_view &>(cxx::fn::revStrOverloadValCRef::id)
                                 .build(&revStrOverloadValCRef));

        fns.push_back(rtl::type().function<void>(cxx::fn::reverseString::id)
                                 .build(&reverseString));

        fns.push_back(rtl::type().function<const char *>(cxx::fn::reverseString::id)
                                 .build(&reverseString));

        fns.push_back(rtl::type().function<std::string>(cxx::fn::reverseString::id)
                                 .build(&reverseString));

        fns.push_back(rtl::type().function<std::string &>(cxx::fn::reverseString::id)
                                 .build(&reverseString));

        fns.push_back(rtl::type().function<std::string &&>(cxx::fn::reverseString::id)
                                 .build(&reverseString));

        fns.push_back(rtl::type().function<const std::string &>(cxx::fn::reverseString::id)
                                 .build(&reverseString));

        fns.push_back(rtl::type().function<std::string *>(cxx::fn::reverseString::id)
                                 .build(&reverseString));

        fns.push_back(rtl::type().function<const std::string *>(cxx::fn::reverseString::id)
                                 .build(&reverseString));

        fns.push_back(rtl::type().function(cxx::fn::revStrConstRefArg::id)
                                 .build(&revStrConstRefArg));

        fns.push_back(rtl::type().function(cxx::fn::revStrRValueRefArg::id)
                                 .build(&revStrRValueRefArg));

        fns.push_back(rtl::type().function(cxx::fn::revStrNonConstRefArg::id)
                                 .build(&revStrNonConstRefArg));

        fns.push_back(rtl::type().function<std::string_view &>(cxx::fn::revStrOverloadRefAndCRef::id)
                                 .build(&revStrOverloadRefAndCRef));

        fns.push_back(rtl::type().function<const std::string_view &>(cxx::fn::revStrOverloadRefAndCRef::id)
                                 .build(&revStrOverloadRefAndCRef));

        fns.push_back(rtl::type().function<std::string_view>(cxx::fn::revStrOverloadValRef::id)
                                 .build(&revStrOverloadValRef));

        fns.push_back(rtl::type().function<std::string_view &>(cxx::fn::revStrOverloadValRef::id)
                                 .build(&revStrOverloadValRef));
    }
}

