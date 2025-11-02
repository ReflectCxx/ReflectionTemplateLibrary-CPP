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

#include <string_view>

namespace rtl 
{
    enum class error
    {
        None,
        EmptyRObject,
        InvalidCaller,
        NotWrapperType,

        TargetMismatch,
        SignatureMismatch,
        RefBindingMismatch,
        ExplicitRefBindingRequired,
        InvalidStaticMethodCaller,
        InvalidNonStaticMethodCaller,

        CloningDisabled,       //Used only in case of cloning is disabled e.g, unregistered type returnd from a function.
        FunctionNotRegistered,   //Not used by RTL at all, for external purpose only.

        IllegalConstCast,
        ConstOverloadMissing,
        NonConstOverloadMissing,

        TypeNotCopyConstructible,
        TypeNotDefaultConstructible,

        StlWrapperHeapAllocForbidden,
    };


    inline const std::string_view to_string(error err)
    {
        switch (err) {
        case error::None:
            return "No error (operation successful)";
        case error::EmptyRObject:
            return "Empty instance: RObject does not hold any reflected object";
        case error::SignatureMismatch:
            return "Signature mismatch: Function parameters do not match the expected signature";
        case error::RefBindingMismatch:
            return "Reference binding mismatch: Argument references do not match the expected parameter bindings";
        case error::ExplicitRefBindingRequired:
            return "Explicit reference binding required for correct overload resolution";
        case error::InvalidCaller:
            return "Invalid callable: rtl::function/rtl::method object being used is empty.";
        case error::InvalidStaticMethodCaller:
            return "Invalid callable: rtl::method being used to call a static method; use rtl::static_method instead.";
        case error::InvalidNonStaticMethodCaller:
            return "Invalid callable: rtl::static_method being used to call a non-static method; use rtl::method instead.";
        case error::CloningDisabled:
            return "Type not registered: The requested type is not explicitly registered in the Reflection system";
        case error::FunctionNotRegistered:
            return "Function not registered: The requested erase_function/method is not registered in the Reflection system";
        case error::TargetMismatch:
            return "The object you're trying to bind doesn't match the expected type of the method.";
        case error::NonConstOverloadMissing:
            return "Non-const method not found: The method does not have a non-const overload as explicitly requested.";
        case error::TypeNotCopyConstructible:
            return "Copy constructor inaccessible: Underlying type has deleted or private copy constructor; cannot copy-construct reflected instance";
        case error::TypeNotDefaultConstructible:
            return "Type cannot be default constructed - std::is_default_constructible<T> validation failed";
        case error::ConstOverloadMissing:
            return "Cannot call non-const method on const target implicitly, bind methodQ::NonConst to override.";
        case error::IllegalConstCast:
            return "Illegal const_cast attempt - cannot remove const qualifier from originally-const object";
        case error::StlWrapperHeapAllocForbidden:
            return "Heap allocation forbidden for STL-wrapped objects (smart pointers/optionals/reference_wrappers). use alloc::Stack.";
        default:
            return "Unknown error";
        }
    }
}