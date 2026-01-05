#include <Reflect.hpp>

#include "StringConstOverload.h"
#include "Registration.h"
#include "GlobalTestUtils.h"

using namespace test_utils;

namespace test_mirror
{
    void Register::typeIdStringConstOverload(std::unordered_map<std::string, rtl::traits::uid_t>& id)
    {
        const StrConstOverload obj;
        obj.reverseString();

        id.insert(std::make_pair(StrConstOverload::struct_, rtl::traits::uid<StrConstOverload>::value));
    }

    void Register::typeStringConstOverload(std::vector<rtl::Function>& fns)
    {
        fns.push_back(rtl::type().record<StrConstOverload>(StrConstOverload::struct_)
                                 .build());

        fns.push_back(rtl::type().member<StrConstOverload>()
                                 .method(str_reverseString)
                                 .build(&StrConstOverload::reverseString));

        fns.push_back(rtl::type().member<StrConstOverload>()
                                 .methodConst(str_reverseString)
                                 .build(&StrConstOverload::reverseString));
    }
}