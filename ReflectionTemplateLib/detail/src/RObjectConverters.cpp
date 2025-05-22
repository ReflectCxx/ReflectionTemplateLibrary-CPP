
#include "TypeId.hpp"
#include "RObjectConverters.hpp"

namespace rtl::detail
{
    template<>
    template<>
    void RObjectConverter<std::string>::pushConversion<const char*>()
    {
        const auto& converter = [](const std::any& pSrc)-> std::any
        {
            auto& srcStr = std::any_cast<const std::string&>(pSrc);
            return std::any(static_cast<const char*>(srcStr.c_str()));
        };
        conversions().emplace_back(std::pair(TypeId<const char*>::get(), converter));
    }


    template<>
    bool RObjectConverter<std::string>::pushKnownConversions()
    {
        pushConversion<const char*>();
        return false;
    }
}