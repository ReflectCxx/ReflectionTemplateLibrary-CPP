/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#include <rtl/rtl_typeid.h>
#include <detail/inc/ReflectCast.hpp>
#include <detail/inc/RObjectUPtr.h>

namespace rtl::detail
{
    template<>
    template<>
    void ReflectCast<std::string>::pushConversion<char>()
    {
        const auto& conversion = [](const std::any& pSrc, const EntityKind& pSrcEntityKind, EntityKind& pNewEntityKind)-> std::any
        {
            try {
                pNewEntityKind = EntityKind::Ptr;
                const auto& isPtr = (pSrcEntityKind == EntityKind::Ptr);
                // GCOVR_EXCL_START
                if (pSrcEntityKind == EntityKind::Wrapper) {
                    //TODO: Will fail for any other wrapper other than 'RObjectUPtr<>'.
                    const auto& srcRUptr = std::any_cast<const RObjectUPtr<std::string>&>(pSrc);
                    return std::any(srcRUptr.get()->c_str());
                }
                // GCOVR_EXCL_STOP
                else {
                    const auto& srcObj = (isPtr ? *std::any_cast<const std::string*>(pSrc) : std::any_cast<const std::string&>(pSrc));
                    return std::any(srcObj.c_str());
                }
            }
            // GCOVR_EXCL_START
            catch (const std::exception&) {
                pNewEntityKind = EntityKind::None;
                return std::any();
            }
            // GCOVR_EXCL_STOP
        };
        conversions().emplace_back(std::pair(traits::uid<char>::value, conversion));
    }


    template<>
    template<>
    void ReflectCast<std::string_view>::pushConversion<char>()
    {
        const auto& conversion = [](const std::any& pSrc, const EntityKind& pSrcEntityKind, EntityKind& pNewEntityKind)-> std::any
        {
            try {
                pNewEntityKind = EntityKind::Ptr;
                const auto& isPtr = (pSrcEntityKind == EntityKind::Ptr);
                // GCOVR_EXCL_START
                if (pSrcEntityKind == EntityKind::Wrapper) {
                    //TODO: Will fail for any other wrapper other than 'RObjectUPtr<>'.
                    const auto& srcRUptr = std::any_cast<const RObjectUPtr<std::string>&>(pSrc);
                    return std::any(srcRUptr.get()->data());
                }
                // GCOVR_EXCL_STOP
                else {
                    const auto& srcObj = (isPtr ? *std::any_cast<const std::string_view*>(pSrc) : std::any_cast<const std::string_view&>(pSrc));
                    return std::any(srcObj.data());
                }
            }
            // GCOVR_EXCL_START
            catch (const std::exception&) {
                pNewEntityKind = EntityKind::None;
                return std::any();
            }
            // GCOVR_EXCL_STOP
        };
        conversions().emplace_back(std::pair(traits::uid<char>::value, conversion));
    }


    template<>
    template<>
    void ReflectCast<std::string_view>::pushConversion<std::string>()
    {
        using _toType = std::string;
        const auto& conversion = [](const std::any& pSrc, const EntityKind& pSrcEntityKind, EntityKind& pNewEntityKind)-> std::any
        {
            try {
                pNewEntityKind = EntityKind::Value;
                const auto& isPtr = (pSrcEntityKind == EntityKind::Ptr);
                // GCOVR_EXCL_START
                if (pSrcEntityKind == EntityKind::Wrapper) {
                    //TODO: Will fail for any other wrapper other than 'RObjectUPtr<>'.
                    const auto& srcRUptr = std::any_cast<const RObjectUPtr<std::string_view>&>(pSrc);
                    return std::any(_toType(*srcRUptr.get()));
                }
                // GCOVR_EXCL_STOP
                else {
                    const auto& srcObj = (isPtr ? *std::any_cast<const std::string_view*>(pSrc) : std::any_cast<const std::string_view&>(pSrc));
                    return std::any(_toType(srcObj));
                }
            }
            // GCOVR_EXCL_START
            catch (const std::exception&) {
                pNewEntityKind = EntityKind::None;
                return std::any();
            }
            // GCOVR_EXCL_STOP
        };
        conversions().emplace_back(std::pair(traits::uid<_toType>::value, conversion));
    }
}