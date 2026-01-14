/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <memory>
#include <optional>
#include <unordered_map>

#include <inc/Method.h>

namespace rtl 
{
/*  @class: Record
    * represents a reflected class/struct.
    * contains registered member-functions as 'Method' objects.
    * provides interface to access methods by name.
    * provides interface to construct instances of the class/struct using the registered constructors.
*/  class Record
    {
        using MethodMap = std::unordered_map< std::string, Method >;

        mutable traits::uid_t m_recordId;
        mutable std::string m_namespaceStr;
        mutable std::string m_recordName;
        mutable MethodMap m_methods;

    private:

        Record(const std::string& pRecordName, const traits::uid_t pRecordId, const std::string& pNamespace)
            : m_recordId(pRecordId)
            , m_namespaceStr(pNamespace)
            , m_recordName(pRecordName)
        { }

        GETTER_REF_C(MethodMap, FunctionsMap, m_methods)

    public:

        Record() = delete;
        Record(Record&&) = default;
        Record(const Record&) = default;
        Record& operator=(Record&&) = default;
        Record& operator=(const Record&) = default;

        GETTER_CREF(MethodMap, MethodMap, m_methods)
        GETTER_CREF(std::string, RecordName, m_recordName)
        
        template<class ...args_t>
        constructor<args_t...> ctor() const;

/*      @method: getMethod
        @param: const std::string& (name of the method)
        @return: std::optional<Method>
        * if the method isn't found by the given name, std::nullopt is returned.
*/      std::optional<Method> getMethod(const std::string& pMethod) const
        {
            const auto& itr = m_methods.find(pMethod);
            if (itr != m_methods.end()) {
                return std::optional(itr->second);
            }
            return std::nullopt;
        }

        //only class which can create objects of this class & manipulates 'm_methods'.
        friend class detail::CxxReflection;
    };
}