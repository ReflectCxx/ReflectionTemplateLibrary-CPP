#pragma once

#include <string>
#include <type_traits>
#include <functional>
#include <any>

namespace rtl {

    // Utility: Remove const and reference qualifiers from T.
    template <typename T>
    using remove_const_n_reference = std::remove_const_t<std::remove_reference_t<T>>;

    // Utility: Remove const from T if T is not a reference; otherwise, leave as is.
    template <typename T>
    using remove_const_if_not_reference = std::conditional_t< std::is_reference_v<T>, T, std::remove_const_t<T>>;

    // Utility: Remove const, reference, and pointer from T (after decay).
    template<typename T>
    using remove_const_n_ref_n_ptr = std::remove_const_t<std::remove_reference_t<std::remove_pointer_t<std::decay_t<T>>>>;

    enum class ConversionKind
    {
        ByRef,
        ByValue,
        NotDefined,
        BadAnyCast
    };

    enum class IsPointer { Yes, No };

    using Converter = std::function< std::any(const std::any&, const IsPointer&, ConversionKind&) >;

    enum FunctorIdx
    {
        ZERO = 0,   //heap constructor index
        ONE = 1,    //destructor index
        TWO = 2,    //copy constructor index
        MAX_SIZE = 3
    };


    //Type Qualifier.
    enum class TypeQ
    {
        None,
        Mute,       //Mutable
        Const,      //Constant
        //ConstRef    //Constant Reference
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
        EmptyInstance,
        InvalidAllocType,
        SignatureMismatch,
        InstanceTypeMismatch,
        InstanceConstMismatch,
        CopyConstructorDisabled,
        ReflectedFunctionNotFound,
        ReflectedConstructorNotFound,
        InstanceOnStackDisabledNoCopyCtor
    };

    static constexpr std::size_t invalid_index = static_cast<std::size_t>(-1);

    struct CtorName
    {
        inline static const std::string dctor(const std::string& pRecordName) {
            return (pRecordName + "::~" + pRecordName + "()");
        }

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
        case error::None: return "None";
        case error::EmptyInstance: return "EmptyInstance";
        case error::InvalidAllocType: return "InvalidAllocType";
        case error::SignatureMismatch: return "SignatureMismatch";
        case error::InstanceTypeMismatch: return "InstanceTypeMismatch";
        case error::InstanceConstMismatch: return "InstanceConstMismatch";
        case error::ReflectedFunctionNotFound: return "ReflectedFunctionNotFound";
        case error::ReflectedConstructorNotFound: return "ReflectedConstructorNotFound";
        case error::CopyConstructorDisabled: return "CopyConstructorDisabled";
        case error::InstanceOnStackDisabledNoCopyCtor: return "InstanceOnStackDisabledNoCopyCtor";
        default: return "Unknown";
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