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
        mutable std::string m_recordName;
        mutable MethodMap m_methods;

    private:

        Record(const std::string& pRecordName, const traits::uid_t pRecordId)
            : m_recordId(pRecordId)
            , m_recordName(pRecordName)
        { }

        constexpr MethodMap& getFunctionsMap() const;

    public:

        Record() = delete;
        Record(Record&&) = default;
        Record(const Record&) = default;
        Record& operator=(Record&&) = default;
        Record& operator=(const Record&) = default;

        constexpr const MethodMap& getMethodMap() const;
        constexpr const std::string& getRecordName() const;
        
        template<class ...args_t>
        constructor<args_t...> ctorT() const;

/*      @method: getMethod
        @param: const std::string& (name of the method)
        @return: std::optional<Method>
        * if the method isn't found by the given name, std::nullopt is returned.
*/      std::optional<Method> getMethod(std::string_view pMethod) const
        {
            const auto& itr = m_methods.find(std::string(pMethod));
            if (itr != m_methods.end()) {
                return std::optional(itr->second);
            }
            return std::nullopt;
        }

        //only class which can create objects of this class & manipulates 'm_methods'.
        friend class detail::CxxReflection;
    };
}


namespace rtl
{
    constexpr Record::MethodMap& Record::getFunctionsMap() const {
        return m_methods;
    }

    constexpr const Record::MethodMap& Record::getMethodMap() const {
        return m_methods;
    }

    constexpr const std::string& Record::getRecordName() const {
        return m_recordName;
    }
}