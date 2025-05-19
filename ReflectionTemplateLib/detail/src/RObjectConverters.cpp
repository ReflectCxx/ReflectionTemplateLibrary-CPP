
#include "TypeId.hpp"
#include "RObjectConverters.hpp"


namespace rtl::detail
{
    template<class _fromType>
    std::vector<std::pair<std::size_t, Converter>> RObjectConverter<_fromType>::m_converters;
}


namespace
{
    //forcing linker to consider linking this TU.
    static auto _ = rtl::detail::RObjectConverter<std::string>::getConversions().size();
}

namespace rtl::detail 
{
    template<>
    template<>
    void RObjectConverter<std::string>::pushConversion<const char*>()
    {
        const auto& converter = [](const std::any& pSrc)-> std::any
        {
            auto srcStr = std::any_cast<const std::string&>(pSrc).c_str();
            return std::make_any<const char*>(srcStr);
        };
        m_converters.emplace_back(std::pair(TypeId<const char*>::get(), converter));
    }
}