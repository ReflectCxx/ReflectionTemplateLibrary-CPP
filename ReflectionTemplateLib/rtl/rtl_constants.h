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

#include "rtl_errors.h"

namespace rtl {

    // Allocation policy for rtl::RObject.
    //
    // Determines how the underlying object is created and managed at runtime.
    // RTL enforces strict RAII semantics: no explicit destroy API exists, and
    // cleanup is always automatic.
    enum class alloc
    {
        None = 0,/*
                 * Assigned to empty or moved-from RObjects.
                 * - Represents an invalid / non-owning state.
                 * - Any attempt to call or clone results in rtl::error::EmptyRObject.
                 */

        Heap,   /*
                 * Assigned to RTL-allocated heap objects.
                 * - Internally managed via std::unique_ptr<T>.
                 * - Moving transfers ownership of the unique_ptr (cheap, no deep copy).
                 * - Destroyed automatically when the owning RObject goes out of scope.
                 * - User never sees the unique_ptr; wrapper details remain hidden.
                 */

        Stack   /*
                 * Assigned to return values and RTL-allocated stack objects.
                 * - The object instance lives directly inside the RObject.
                 * - Moving calls the reflected type's move constructor.
                 * - Destroyed automatically at scope exit (like any local variable).
                 */
    };


    // Cloning policy for rtl::RObject.
    enum class copy
    {
        /*
        * An rtl::RObject may internally hold values wrapped in std::optional,
        * std::reference_wrapper, or smart pointers. The copy policy gives users
        * control over whether cloning should duplicate the wrapper itself or
        * perform a deep copy of the underlying object.
        *
        * Auto (default):
        *   - RTL first attempts a wrapper-level copy if the wrapper is copyable.
        *   - If the wrapper is an internal detail (e.g., heap objects stored in
        *     std::unique_ptr), RTL transparently performs a deep copy of the
        *     underlying object instead of copying the wrapper.
        *   - This ensures correct semantics even when the user is unaware of
        *     wrapper details (typical in reflection use cases).
        *   - When explicitly requested, users can still attempt Value or Wrapper
        *     cloning; RTL will return success or a detailed error as appropriate.
        *
        * Value:
        *   - Always perform an independent deep copy of the underlying object.
        *
        * Wrapper:
        *   - Copy the wrapper itself, without cloning the underlying object.
        */
        Auto,
        Value,
        Wrapper
    };


    // Utility wrapper for const-correctness control in overload resolution.
    //
    // Used to explicitly request that RTL treat an rtl::RObject as non-const
    // when invoking member functions. Mirrors the intent of const_cast in C++,
    // but with provenance-aware safety: it works only if the object was not
    // originally declared const.
    template<class T>
    struct constCast
    {
        const T& m_target;

        constCast() = delete;
        constCast(constCast&&) = delete;
        constCast(const constCast&) = delete;

        explicit constCast(const T& target) : m_target(target) {}
    };

    // Invalid number/index.
    static constexpr std::size_t index_none = static_cast<std::size_t>(-1);
}



namespace rtl::detail 
{
    enum class EntityKind
    {
        None = 0,
        Ptr,
        Value,
        Wrapper
    };

    enum class Wrapper
    {
        None = 0,
        Any,
        Weak,
        Unique,
        Shared,     //Planned.
        Variant,    //Planned.
        Optional,   //Planned.
        Reference   //Planned.
    };

    enum Index 
    {
        Ctor = 0,
        CopyCtor
    };


    // MethodQ: Method qualifier + static marker.
    enum class methodQ
    {
        None = 0,   // Static method (no const/non-const qualifier)
        Const,      // Const-qualified instance method
        NonConst    // Non-const instance method
    };

    constexpr const std::string_view NAMESPACE_GLOBAL = "global";

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

#if defined(_MSC_VER)
#define FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define FORCE_INLINE inline __attribute__((always_inline))
#else
#define FORCE_INLINE inline
#endif
}