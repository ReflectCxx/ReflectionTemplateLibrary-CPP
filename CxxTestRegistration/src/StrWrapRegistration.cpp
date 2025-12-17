
#include <Reflect.hpp>

#include "StringWrap.h"
#include "Registration.h"
#include "GlobalTestUtils.h"

using namespace test_utils;

namespace test_mirror
{
    void addTypeIdStringWrap(std::unordered_map<std::string, std::size_t>& id)
    {
        id.insert(std::make_pair(StrWrap::struct_, rtl::detail::TypeId<StrWrap>::get()));
    }

	void registerTypeStringWrap(std::vector<rtl::Function>& fns)
	{
        // Registers default constructor as well.
        fns.push_back(rtl::type().record<StrWrap>(StrWrap::struct_)
                                 .build());

        fns.push_back(rtl::type().member<StrWrap>()
                                 .constructor<std::string&>()
                                 .build());

        fns.push_back(rtl::type().member<StrWrap>()
                                 .constructor<std::string&&>()
                                 .build());

        fns.push_back(rtl::type().member<StrWrap>()
                                 .constructor<const std::string&>()
                                 .build());

        fns.push_back(rtl::type().member<StrWrap>()
                                 .constructor<const char*>()
                                 .build());

        fns.push_back(rtl::type().member<StrWrap>()
                                 .constructor<std::string_view>()
                                 .build());
	}
}