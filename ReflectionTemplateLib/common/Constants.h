#pragma once

#include <string>

namespace rtl {

    enum class IsPointer 
    { 
        No,
        Yes
    };


    enum class Wrapper
    {
        None,
        Weak,
        Unique,
        Shared
    };


    enum class ConversionKind
    {
        ByRef,
        ByValue,
        NotDefined,
        BadAnyCast
    };


    enum FunctorIdx
    {
        ZERO = 0,   //heap constructor index
        ONE = 1,    //copy constructor index
        MAX_SIZE = 2
    };


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
        None = -1,
        Stack = 0,
        Heap = 1,
    };


    //Qualifier type.
    enum class ConstructorType
    {
        None,
        Ctor,
        CopyCtor
    };


    enum class error
    {
        None,
        EmptyRObject,
        SignatureMismatch,
        MethodTargetMismatch,
        AmbiguousConstOverload,
        FunctionNotRegisterdInRTL,
        ConstMethodOverloadNotFound,
        ConstructorNotRegisteredInRTL,
        NonConstMethodOverloadNotFound,
        CopyConstructorPrivateOrDeleted,
    };

    static constexpr std::size_t index_none = static_cast<std::size_t>(-1);

    struct CtorName
    {
        inline static const std::string ctor(const std::string& pRecordName) {
            return (pRecordName + "::" + pRecordName + "()");
        }

        inline static const std::string copyCtor(const std::string& pRecordName) {
            return (pRecordName + "::" + pRecordName + "(const " + pRecordName + "&)");
        }
    };


    inline const char* to_string(error err) 
    {
        switch (err) {
        case error::None: 
            return "No error (operation successful)";
        case error::EmptyRObject:
            return "Empty instance: RObject does not hold any reflected object";
        case error::SignatureMismatch:
            return "Signature mismatch: Function parameters do not match the expected signature";
        case error::FunctionNotRegisterdInRTL:
            return "Function not registered: The requested method is not registered in the Reflection system";
        case error::MethodTargetMismatch:
            return "The object you're trying to bind doesn't match the expected type of the method.";
        case error::AmbiguousConstOverload:
            return "Ambiguous overload: Both const and non-const methods are registered; explicitly specify MethodQ to resolve.";
        case error::ConstMethodOverloadNotFound:
            return "Const-qualified method not found: The method does not have a const-qualified overload as explicitly requested.";
        case error::NonConstMethodOverloadNotFound:
            return "Non-const method not found: The method does not have a non-const overload as explicitly requested.";
        case error::ConstructorNotRegisteredInRTL:
            return "Constructor not registered: No constructor registered for the requested type in the Reflection system";
        case error::CopyConstructorPrivateOrDeleted:
            return "Copy constructor inaccessible: Underlying type has deleted or private copy constructor; cannot copy-construct reflected instance";
        default:
            return "Unknown error";
        }
    }


    constexpr const char* NAMESPACE_GLOBAL = "namespace_global";


#define GETTER(_varType, _name, _var)                       \
    inline constexpr const _varType& get##_name() const {   \
        return _var;                                        \
    }


#define GETTER_REF(_varType, _name, _var)       \
    inline _varType& get##_name() const {       \
        return _var;                            \
    }


#define GETTER_BOOL(_name, _var)              \
    inline const bool is##_name() const {     \
        return _var;                          \
    }
}