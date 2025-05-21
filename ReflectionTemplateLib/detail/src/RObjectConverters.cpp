
#include "TypeId.hpp"
#include "RObjectConverters.h"

namespace rtl::detail
{
    template<>
    const std::vector<std::pair<std::size_t, Converter>>& RObjectConverter<std::string>::getConversions()
    {
        return m_converters;
    }


    template<>
    template<>
    void RObjectConverter<std::string>::pushConversion<const char*>()
    {
        const auto& converter = [](const std::any& pSrc)-> std::any
        {
            auto& srcStr = std::any_cast<const std::string&>(pSrc);
            return std::any(static_cast<const char*>(srcStr.c_str()));
        };
        m_converters.emplace_back(std::pair(TypeId<const char*>::get(), converter));
    }


    template<>
    bool RObjectConverter<std::string>::addKnownConversions()
    {
        pushConversion<const char*>();
        return false;
    }
}