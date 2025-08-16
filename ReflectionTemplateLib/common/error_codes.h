/*_________________________________________________________________________
* Copyright 2025 Neeraj Singh (reflectcxx@outlook.com)
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
___________________________________________________________________________*/

#pragma once

#include <string_view>

namespace rtl 
{
    enum class error
    {
        None,
        EmptyRObject,

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