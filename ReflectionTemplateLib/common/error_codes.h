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
        NotWrapperType,

        TargetMismatch,
        SignatureMismatch,
        FunctionNotRegisterd,
        ConstructorNotRegistered,

        IllegalConstCast,
        ConstCallViolation,
        ConstOverloadMissing,
        AmbiguousConstOverload,
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
        case error::FunctionNotRegisterd:
            return "Function not registered: The requested function/method is not registered in the Reflection system";
        case error::TargetMismatch:
            return "The object you're trying to bind doesn't match the expected type of the method.";
        case error::AmbiguousConstOverload:
            return "Ambiguous overload: Both const and non-const methods are registered; explicitly specify MethodQ to resolve.";
        case error::ConstOverloadMissing:
            return "Const-qualified method not found: The method does not have a const-qualified overload as explicitly requested.";
        case error::NonConstOverloadMissing:
            return "Non-const method not found: The method does not have a non-const overload as explicitly requested.";
        case error::ConstructorNotRegistered:
            return "Constructor not registered: No constructor registered for the requested type in the Reflection system";
        case error::TypeNotCopyConstructible:
            return "Copy constructor inaccessible: Underlying type has deleted or private copy constructor; cannot copy-construct reflected instance";
        case error::TypeNotDefaultConstructible:
            return "Type cannot be default constructed - std::is_default_constructible<T> validation failed";
        case error::ConstCallViolation:
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