#pragma once

#include <string>
#include <string_view>
#include <type_traits>

namespace rtl {

    constexpr const char* NAMESPACE_GLOBAL = "namespace_global";

    template<typename T>
    struct is_string_like : std::false_type {};

    template<>
    struct is_string_like<std::string> : std::true_type {};

    template<>
    struct is_string_like<std::string_view> : std::true_type {};

    template<>
    struct is_string_like<char*> : std::true_type {};

    template<>
    struct is_string_like<const char*> : std::true_type {};

    template<std::size_t N>
    struct is_string_like<const char[N]> : std::true_type {};

    template <typename T>
    using remove_const_and_reference = std::remove_const_t<std::remove_reference_t<T>>;

    template <typename T>
    using remove_const_if_not_reference = std::conditional_t< std::is_reference_v<T>, T, std::remove_const_t<T>>;


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


    enum FunctorIdx
    {
        ZERO = 0,   //heap constructor index
        ONE,    //destructor index
        TWO,    //copy constructor index
        MAX_SIZE
    };


    //Qualifier type.
    enum class TypeQ
    {
        None,
        Mute,   //Mutable
        Const,  //Constant
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


    enum class Error
    {
        None,
        EmptyInstance,
        InvalidAllocType,
        SignatureMismatch,
        InstanceTypeMismatch,
        InstanceConstMismatch,
        ConstructorNotFound,
        CopyConstructorDisabled,
        InstanceOnStackDisabledNoCopyCtor
    };


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


    inline const char* to_string(Error err) 
    {
        switch (err) {
        case Error::None: return "None";
        case Error::EmptyInstance: return "EmptyInstance";
        case Error::InvalidAllocType: return "InvalidAllocType";
        case Error::SignatureMismatch: return "SignatureMismatch";
        case Error::InstanceTypeMismatch: return "InstanceTypeMismatch";
        case Error::InstanceConstMismatch: return "InstanceConstMismatch";
        case Error::ConstructorNotFound: return "ConstructorNotFound";
        case Error::CopyConstructorDisabled: return "CopyConstructorDisabled";
        case Error::InstanceOnStackDisabledNoCopyCtor: return "InstanceOnStackDisabledNoCopyCtor";
        default: return "Unknown";
        }
    }
}