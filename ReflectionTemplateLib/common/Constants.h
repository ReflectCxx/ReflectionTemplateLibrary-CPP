#pragma once

#include <string_view>

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

    enum class error
    {
        None,
        EmptyRObject,
        SignatureMismatch,
        MethodTargetMismatch,
        AmbiguousConstOverload,
        FunctionNotRegisterdInRtl,
        ConstMethodOverloadNotFound,
        ConstructorNotRegisteredInRtl,
        NonConstMethodOverloadNotFound,
        NonConstMethodCallOnConstTarget,
        TrueConstTargetConstCastDisallowed,
        ReflectingUniquePtr_copyDisallowed,
        ReflectingStlWrapper_copyOnHeapDisallowed,

        Instantiating_typeVoid,
        Instantiating_typeAbstract,
        Instantiating_typeFunction,
        Instantiating_typeIncomplete,
        Instantiating_typeNotDefaultConstructible,
        Instantiating_typeNotCopyConstructible,
        Instantiating_typeNotMoveConstructible
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
        case error::FunctionNotRegisterdInRtl:
            return "Function not registered: The requested method is not registered in the Reflection system";
        case error::MethodTargetMismatch:
            return "The object you're trying to bind doesn't match the expected type of the method.";
        case error::AmbiguousConstOverload:
            return "Ambiguous overload: Both const and non-const methods are registered; explicitly specify MethodQ to resolve.";
        case error::ConstMethodOverloadNotFound:
            return "Const-qualified method not found: The method does not have a const-qualified overload as explicitly requested.";
        case error::NonConstMethodOverloadNotFound:
            return "Non-const method not found: The method does not have a non-const overload as explicitly requested.";
        case error::ConstructorNotRegisteredInRtl:
            return "Constructor not registered: No constructor registered for the requested type in the Reflection system";
        case error::Instantiating_typeNotCopyConstructible:
            return "Copy constructor inaccessible: Underlying type has deleted or private copy constructor; cannot copy-construct reflected instance";
        case error::ReflectingUniquePtr_copyDisallowed:
            return "Cannot copy RObject reflecting std::unique_ptr - copy disallowed to preserve ownership.";
        case error::NonConstMethodCallOnConstTarget:
            return "Cannot call non-const method on const target implicitly, bind methodQ::NonConst to override.";
        default:
            return "Unknown error";
        }
    }
}


namespace rtl::detail 
{
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

    enum class Contains
    {
        None,
        Value,
        Pointer,
        Wrapper,
        ConstWrapper
    };

    enum class ConversionKind
    {
        ByRef,
        ByValue,
        NotDefined,
        BadAnyCast
    };
    
    inline static const std::string ctor_name(const std::string& pRecordName) {
        return (pRecordName + "::" + pRecordName + "()");
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