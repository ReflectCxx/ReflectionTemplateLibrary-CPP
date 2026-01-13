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

namespace rtl {

    // Allocation policy for rtl::RObject.
    //
    // Determines how the underlying object is created and managed at runtime.
    // RTL enforces strict RAII semantics: no explicit destroy API exists, and
    // cleanup is always automatic.
    enum class alloc
    {
        None,   /*
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
        * An rtl::RObject may internally hold value wrapped in std::optional,
        * std::reference_wrapper, or smart pointers. The copy policy gives users
        * control over whether cloning should duplicate the wrapper itself or
        * perform a deep copy of the underlying object.
        *
        * Auto (default):
        *   - RTL first attempts a wrapper-level copy if the wrapper is copyable.
        *   - If the wrapper is an internal detail (e.g., heap objects created via
        *     RTL, stored in std::unique_ptr), RTL transparently performs a deep
        *     copy of the underlying object instead of copying the wrapper.
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

    // Invalid number/index.
    static constexpr std::size_t index_none = static_cast<std::size_t>(-1);
}



namespace rtl::detail 
{
    enum class EntityKind
    {
        None,
        Ptr,
        Value,
        Wrapper
    };

    enum class Wrapper
    {
        None,
        Any,
        Weak,
        Unique,
        Shared,     //Planned.
        Variant,    //Planned.
        Optional,   //Planned.
        Reference   //Planned.
    };

    enum class member
    {
        None,       // non-member functions.
        Const,      // Const-qualified instance method
        NonConst,   // Non-const instance method
        Static,     // Static methods
        UserCtor,
        DefaultCtor
    };

    constexpr const char* INIT_LATER = "";
    constexpr const char* RECORD_NONE = "";
    constexpr const char* NAMESPACE_GLOBAL = "rtl::global";

    inline static const std::string ctor_name(const std::string_view pRecordName) {
    //  [critical] Must not change. Constructors are identified using this format.
        return (std::string(pRecordName) + "::" + std::string(pRecordName) + "()");
    }

#define GETTER(_varType, _name, _var)                      \
    inline constexpr const _varType get##_name() const {   \
        return _var;                                       \
    }

#define GETTER_REF_C(_varType, _name, _var)           \
    inline constexpr _varType& get##_name() const {   \
        return _var;                                  \
    }

#define GETTER_REF(_varType, _name, _var)       \
    inline constexpr _varType& get##_name() {   \
        return _var;                            \
    }

#define GETTER_CPTR(_varType, _name, _var)                 \
    inline constexpr const _varType* get##_name() const {  \
        return _var;                                       \
    }

#define GETTER_CREF(_varType, _name, _var)       \
    inline constexpr const _varType& get##_name() const {  \
        return _var;                             \
    }

#define GETTER_BOOL(_name, _var)              \
    inline constexpr const bool is##_name() const {     \
        return _var;                          \
    }

#if defined(_MSC_VER)
#define ForceInline __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define ForceInline inline __attribute__((always_inline))
#else
#define ForceInline inline
#endif
}