
#include "ReflectCast.hpp"
#include "ReflectCastUtil.h"


namespace rtl::detail
{
    template<>
    template<>
    void ReflectCast<std::string>::pushConversion<const char*>();
}


namespace rtl::detail
{
    void ReflectedConversions::init()
    {
        ReflectCast<std::string>::pushConversion<const char*>();
        ReflectCast<std::string>::pushConversion<std::string_view>();

        using _safePODTypes = std::tuple< bool, char, signed char, unsigned char, short, unsigned short, int>;
        auto conversions = make_conversion_pairs<_safePODTypes>();
        register_all_conversions<decltype(conversions)>();
    }
}