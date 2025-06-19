
#include "TypeId.h"
#include "ReflectCast.hpp"

#include <iostream>

namespace rtl::detail
{
    template<>
    template<>
    void ReflectCast<std::string>::pushConversion<const char*>()
    {
        using _toType = const char*;
        const auto& conversion = [](const std::any& pSrc, const rtl::IsPointer& pIsPointer, rtl::ConversionKind& pConverKind)-> std::any
        {
            pConverKind = rtl::ConversionKind::ByValue;
            const auto& isPtr = (pIsPointer == rtl::IsPointer::Yes);
            const auto& srcObj = (isPtr ? *std::any_cast<const std::string*>(pSrc) : std::any_cast<const std::string&>(pSrc));
            return std::any(static_cast<const _toType&>(srcObj.c_str()));
        };

        conversions().emplace_back(std::pair(TypeId<_toType>::get(), conversion));
    }
}