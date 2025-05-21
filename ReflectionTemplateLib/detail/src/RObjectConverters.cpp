
#include "TypeId.hpp"
#include "RObjectConverters.hpp"

namespace rtl::detail
{
    template<>
    const std::vector<std::pair<std::size_t, Converter>>& RObjectConverter<std::string>::getConversions()
    {
        return m_conversions;
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
        m_conversions.emplace_back(std::pair(TypeId<const char*>::get(), converter));
    }


    template<>
    bool RObjectConverter<std::string>::addKnownConversions()
    {
        pushConversion<const char*>();
        return false;
    }
}

namespace {

    //adding known conversions.
    static auto _ = rtl::detail::RObjectConverter<std::string>::addKnownConversions();
}