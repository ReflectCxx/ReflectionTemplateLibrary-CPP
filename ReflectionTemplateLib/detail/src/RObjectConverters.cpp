
#include "TypeId.hpp"
#include "RObjectConverters.hpp"

namespace rtl::detail
{
    template<>
    bool RObjectConverter<std::string>::pushKnownConversions()
    {
        pushConversion<std::string_view>();
        return false;
    }
}