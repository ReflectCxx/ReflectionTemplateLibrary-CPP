
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
        const auto& conversion = [](const std::any& pSrc, const Contains& ContainedAs, ConversionKind& pConversionKind)-> std::any
        {
            pConversionKind = ConversionKind::ByValue;
            const auto& isPtr = (ContainedAs == Contains::Pointer);
            const auto& srcObj = (isPtr ? *std::any_cast<const std::string*>(pSrc) : std::any_cast<const std::string&>(pSrc));
            return std::any(static_cast<const _toType&>(srcObj.c_str()));
        };
        conversions().emplace_back(std::pair(TypeId<_toType>::get(), conversion));
    }


    template<>
    template<>
    void ReflectCast<std::string_view>::pushConversion<const char*>()
    {
        using _toType = const char*;
        const auto& conversion = [](const std::any& pSrc, const Contains& ContainedAs, ConversionKind& pConversionKind)-> std::any
        {
            pConversionKind = ConversionKind::ByValue;
            const auto& isPtr = (ContainedAs == Contains::Pointer);
            const auto& srcObj = (isPtr ? *std::any_cast<const std::string_view*>(pSrc) : std::any_cast<const std::string_view&>(pSrc));
            return std::any(static_cast<const _toType&>(srcObj.data()));
        };
        conversions().emplace_back(std::pair(TypeId<_toType>::get(), conversion));
    }


    template<>
    template<>
    void ReflectCast<std::string_view>::pushConversion<std::string>()
    {
        using _toType = std::string;
        const auto& conversion = [](const std::any& pSrc, const Contains& ContainedAs, ConversionKind& pConversionKind)-> std::any
        {
            pConversionKind = ConversionKind::ByValue;
            const auto& isPtr = (ContainedAs == Contains::Pointer);
            const auto& srcObj = (isPtr ? *std::any_cast<const std::string_view*>(pSrc) : std::any_cast<const std::string_view&>(pSrc));
            return std::any(_toType(srcObj));
        };
        conversions().emplace_back(std::pair(TypeId<_toType>::get(), conversion));
    }
}