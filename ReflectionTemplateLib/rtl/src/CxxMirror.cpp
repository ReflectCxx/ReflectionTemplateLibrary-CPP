/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#include <inc/Record.h>
#include <inc/CxxMirror.h>
#include <detail/inc/ReflectCast.h>

namespace rtl
{
    CxxMirror::CxxMirror(const std::vector<Function>& pFunctions) : detail::CxxReflection(pFunctions)
    {
        rtl::detail::ReflectedConversions::init();
    }

    /**
    * @method getRecord
    * 
    * @param pRecordId The RTL-specific unique type identifier.
    * @return std::optional<rtl::Record>
    *         Returns a valid Record if the type is found; otherwise, std::nullopt.
    *
    * Every registered type `T` is assigned a unique integer type ID, which can be
    * obtained via `rtl::traits::uid<T>::value` and cached for efficient lookup.
    *
    * The primary benefit of using a type ID is that it avoids the need to provide
    * the namespace and type name as strings during lookup. */
    std::optional<Record> CxxMirror::getRecord(const traits::uid_t pRecordId) const
    {
        const auto& recordMap = getRecordIdMap();
        const auto& itr = recordMap.find(pRecordId);
        return (itr == recordMap.end() ? std::nullopt : std::make_optional(itr->second));
    }

    /**
    * @method getRecord
    * 
    * @param pNameSpaceName The namespace under which the type was registered.
    * @param pRecordName    The name of the type to look up.
    * @return std::optional<Record>
    *         Returns a valid Record if the type is found by name in the given namespace group; otherwise, std::nullopt.
    *
    * Retrieves the class or struct registered under the specified namespace. */
    std::optional<Record> CxxMirror::getRecord(const std::string_view pRecordName) const
    {
        const auto& recordMap = getRecordsMap();
        const auto& itr = recordMap.find(std::string(pRecordName));
        if (itr != recordMap.end()) {
            return std::make_optional(itr->second);
        }
        return std::nullopt;
    }

    /**
    * @method getFunction
    * 
    * @param pNameSpaceName The namespace under which the function was registered.
    * @param pFunctionName The name of the function to look up.
    * @return std::optional<Function>
    *         Returns a valid Function if found by name in the given namespace group; otherwise, std::nullopt.
    *
    * Retrieves the non-member function registered under the specified namespace. */
    std::optional<Function> CxxMirror::getFunction(const std::string_view pFunctionName) const
    {
        const auto& functionMap = getFunctionsMap();
        const auto& itr = functionMap.find(std::string(pFunctionName));
        if (itr != functionMap.end()) {
            return std::make_optional(itr->second);
        }
        return std::nullopt;
    }
}