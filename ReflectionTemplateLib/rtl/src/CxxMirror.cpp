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
    * @param pRecordName The name of the class or struct to look up.
    * @return std::optional<rtl::Record>
    *         Returns a valid Record if the type is found by name in default namespace group; otherwise, std::nullopt.
    *
    * All registered classes and structs are grouped under a namespace.
    * If no namespace is specified during registration, NAMESPACE_GLOBAL(the default) is used. */
    std::optional<Record> CxxMirror::getRecord(const std::string& pRecordName) const
    {
        return getRecord(std::string(detail::NAMESPACE_GLOBAL), pRecordName);
    }

    /**
    * @method getFunction
    * 
    * @param pFunctionName The name of the non-member function to look up.
    * @return std::optional<rtl::Function>
    *         Returns a valid Function if found by name in default namespace group; otherwise, std::nullopt.
    *
    * All registered non-member functions are grouped under a namespace.
    * If no namespace is specified during registration, NAMESPACE_GLOBAL(the default) is used. */
    std::optional<Function> CxxMirror::getFunction(const std::string& pFunctionName) const
    {
        return getFunction(std::string(detail::NAMESPACE_GLOBAL), pFunctionName);
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
    std::optional<Record> CxxMirror::getRecord(const std::string& pNameSpaceName, const std::string& pRecordName) const
    {
        const auto& nsRecordMap = getNamespaceRecordMap();
        const auto& itr = nsRecordMap.find(pNameSpaceName);
        if (itr != nsRecordMap.end())
        {
            const auto& recordMap = itr->second;
            const auto& itr0 = recordMap.find(pRecordName);
            if (itr0 != recordMap.end()) {
                return std::make_optional(itr0->second);
            }
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
    std::optional<Function> CxxMirror::getFunction(const std::string& pNameSpaceName, const std::string& pFunctionName) const
    {
        const auto& nsFunctionMap = getNamespaceFunctionsMap();
        const auto& itr = nsFunctionMap.find(pNameSpaceName);
        if (itr != nsFunctionMap.end())
        {
            const auto& functionMap = itr->second;
            const auto& itr0 = functionMap.find(pFunctionName);
            if (itr0 != functionMap.end()) {
                return std::make_optional(itr0->second);
            }
        }
        return std::nullopt;
    }
}