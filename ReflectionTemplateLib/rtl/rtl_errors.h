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

#include <string_view>

namespace rtl 
{
    constexpr const char* errstr_Unknown = "Unknown error.";
    constexpr const char* errstr_None = "No error (operation successful).";
    constexpr const char* errstr_EmptyRObject = "Empty instance: RObject does not hold any reflected object.";
    constexpr const char* errstr_InvalidCaller = "Invalid callable: rtl::function/rtl::method object being used is empty.";
    constexpr const char* errstr_SignatureMismatch = "Signature mismatch: Function parameters do not match the expected signature.";
    constexpr const char* errstr_TargetTypeMismatch = "The object you're trying to bind doesn't match the expected type of the method.";
    constexpr const char* errstr_ReturnTypeMismatch = "returnT<TYPE>(): The specified TYPE do not match the expected function's return type.";
    constexpr const char* errstr_RefBindingMismatch = "Reference binding mismatch: Argument references do not match the expected parameter bindings.";
    constexpr const char* errstr_ExplicitRefBindingRequired = "Explicit reference binding required for correct overload resolution.";
    constexpr const char* errstr_InvalidStaticMethodCaller = "Invalid callable: rtl::method being used to call a static method; use rtl::static_method instead.";
    constexpr const char* errstr_InvalidNonStaticMethodCaller = "Invalid callable: rtl::static_method being used to call a non-static method; use rtl::method instead.";
    constexpr const char* errstr_FunctionNotRegistered = "Function not registered: The requested erase_function/method is not registered in the Reflection system.";
    constexpr const char* errstr_ConstOverloadMissing = "Cannot call non-const method on const target implicitly, bind methodQ::NonConst to override.";
    constexpr const char* errstr_NonConstOverloadMissing = "Non-const method not found: The method does not have a non-const overload as explicitly requested.";
    constexpr const char* errstr_InvalidCallOnConstTarget = "Cannot call a non-const method on an RObject that is reflecting a const object.";
    constexpr const char* errstr_TypeNotCopyConstructible = "Copy constructor inaccessible: Underlying type has deleted or private copy constructor; cannot copy-construct reflected instance.";
    constexpr const char* errstr_TypeNotDefaultConstructible = "Type cannot be default constructed - std::is_default_constructible<T> validation failed.";
    constexpr const char* errstr_StlWrapperHeapAllocForbidden = "Heap allocation forbidden for STL-wrapped objects (smart pointers/optionals/reference_wrappers). use alloc::Stack.";


    enum class error
    {
        None,
        EmptyRObject,
        InvalidCaller,
        NotWrapperType,
        SignatureMismatch,
        TargetTypeMismatch,
        ReturnTypeMismatch,
        RefBindingMismatch,
        ExplicitRefBindingRequired,
        InvalidStaticMethodCaller,
        InvalidNonStaticMethodCaller,
        FunctionNotRegistered,   //Not used by RTL at all, for external purpose only.
        ConstOverloadMissing,
        NonConstOverloadMissing,
        InvalidCallOnConstTarget,
        TypeNotCopyConstructible,
        TypeNotDefaultConstructible,
        StlWrapperHeapAllocForbidden
    };


    inline const std::string_view to_string(error err)
    {
        switch (err) {
        case error::None: return std::string_view(errstr_None);
        case error::EmptyRObject: return std::string_view(errstr_EmptyRObject);
        case error::SignatureMismatch: return std::string_view(errstr_SignatureMismatch);
        case error::ReturnTypeMismatch: return std::string_view(errstr_ReturnTypeMismatch);
        case error::RefBindingMismatch: return std::string_view(errstr_RefBindingMismatch);
        case error::ExplicitRefBindingRequired: return std::string_view(errstr_ExplicitRefBindingRequired);
        case error::InvalidCaller: return std::string_view(errstr_InvalidCaller);
        case error::InvalidStaticMethodCaller: return std::string_view(errstr_InvalidStaticMethodCaller);
        case error::InvalidNonStaticMethodCaller: return std::string_view(errstr_InvalidNonStaticMethodCaller);
        case error::FunctionNotRegistered: return std::string_view(errstr_FunctionNotRegistered);
        case error::TargetTypeMismatch: return std::string_view(errstr_TargetTypeMismatch);
        case error::NonConstOverloadMissing: return std::string_view(errstr_NonConstOverloadMissing);
        case error::InvalidCallOnConstTarget: return std::string_view(errstr_InvalidCallOnConstTarget);
        case error::TypeNotCopyConstructible: return std::string_view(errstr_TypeNotCopyConstructible);
        case error::TypeNotDefaultConstructible: return std::string_view(errstr_TypeNotDefaultConstructible);
        case error::ConstOverloadMissing: return std::string_view(errstr_ConstOverloadMissing);
        case error::StlWrapperHeapAllocForbidden: return std::string_view(errstr_StlWrapperHeapAllocForbidden);
        default: return std::string_view(errstr_Unknown);
        }
    }
}