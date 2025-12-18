
#include <Reflect.hpp>

#include "StringWrap.h"
#include "Registration.h"
#include "GlobalTestUtils.h"

using namespace test_utils;

namespace test_mirror
{
    void addTypeIdStringWrap(std::unordered_map<std::string, std::size_t>& id)
    {
        id.insert(std::make_pair(StrWrapA::struct_, rtl::detail::TypeId<StrWrapA>::get()));
        id.insert(std::make_pair(StrWrapB::struct_, rtl::detail::TypeId<StrWrapB>::get()));
        id.insert(std::make_pair(StrWrapC::struct_, rtl::detail::TypeId<StrWrapC>::get()));
        id.insert(std::make_pair(StrWrapD::struct_, rtl::detail::TypeId<StrWrapD>::get()));
    }

	void registerTypeStringWrap(std::vector<rtl::Function>& fns)
	{
        //------------------StrWrapA--------------------------------
        fns.push_back(rtl::type().record<StrWrapA>(StrWrapA::struct_)   // Registers default constructor as well.
                                 .build());

        fns.push_back(rtl::type().member<StrWrapA>()
                                 .constructor<std::string&>()
                                 .build());

        fns.push_back(rtl::type().member<StrWrapA>()
                                 .constructor<std::string&&>()
                                 .build());

        fns.push_back(rtl::type().member<StrWrapA>()
                                 .constructor<const std::string&>()
                                 .build());

        fns.push_back(rtl::type().member<StrWrapA>()
                                 .constructor<const char*>()
                                 .build());

        fns.push_back(rtl::type().member<StrWrapA>()
                                 .constructor<std::string_view>()
                                 .build());

        //------------------StrWrapB--------------------------------
        fns.push_back(rtl::type().record<StrWrapB>(StrWrapB::struct_)   // Registers default constructor as well.
                                 .build());

        fns.push_back(rtl::type().member<StrWrapB>()
                                 .constructor<std::string&>()
                                 .build());

        fns.push_back(rtl::type().member<StrWrapB>()
                                 .constructor<const std::string&>()
                                 .build());

        //------------------StrWrapC--------------------------------
        fns.push_back(rtl::type().record<StrWrapC>(StrWrapC::struct_)   // Registers default constructor as well.
                                 .build());

        fns.push_back(rtl::type().member<StrWrapC>()
                                 .constructor<std::string&>()
                                 .build());

        //------------------StrWrapD--------------------------------
        fns.push_back(rtl::type().record<StrWrapD>(StrWrapD::struct_)   // Registers default constructor as well.
                                 .build());

        fns.push_back(rtl::type().member<StrWrapD>()
                                 .constructor<const std::string&>()
                                 .build());
	}
}