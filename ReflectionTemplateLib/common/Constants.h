/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                         *
 *                                                                       *
 *************************************************************************/


#pragma once

#include "error_codes.h"

namespace rtl {

    static constexpr std::size_t index_none = static_cast<std::size_t>(-1);

    // MethodQ: Method qualifier + static marker.
    enum class methodQ
    {
        None,       // Static method (no const/non-const qualifier)
        Const,      // Const-qualified instance method
        NonConst    // Non-const instance method
    };


    //Allocation type.
    enum class alloc
    {
        None,       //assigned to empty/moved-from 'RObject's.
        Heap,       //assigned to only rtl-allocated heap objects
        Stack,      //assigned to return-values & rtl-allocated stack objects
    };

    enum class copy 
    {
        Auto,
        Value,
        Wrapper
    };


    namespace access { class RObject; }

    struct constCast
    {
        const access::RObject& m_target;

        constCast() = delete;
        constCast(constCast&&) = delete;
        constCast(const constCast&) = delete;
        constCast(const access::RObject& pTarget) : m_target(pTarget) { }
    };
}


namespace rtl::detail 
{
    enum class EntityKind
    {
        None,
        Ref,
        Value,
        Wrapper
    };

    enum class Wrapper
    {
        None,
        Any,
        Weak,
        Unique,
        Shared,
        Variant,
        Optional,
        Reference
    };


    inline static const std::string ctor_name(const std::string_view pRecordName = "") {
    //  [critical] Must not change. Constructors are identified using this format.
        return (std::string(pRecordName) + "::" + std::string(pRecordName) + "()");
    }

#define GETTER(_varType, _name, _var)                       \
    inline constexpr const _varType& get##_name() const {   \
        return _var;                                        \
    }

#define GETTER_REF(_varType, _name, _var)       \
    inline _varType& get##_name() const {       \
        return _var;                            \
    }

#define GETTER_CREF(_varType, _name, _var)       \
    inline const _varType& get##_name() const {  \
        return _var;                             \
    }

#define GETTER_BOOL(_name, _var)              \
    inline const bool is##_name() const {     \
        return _var;                          \
    }

    constexpr const std::string_view NAMESPACE_GLOBAL = "namespace_global";
}