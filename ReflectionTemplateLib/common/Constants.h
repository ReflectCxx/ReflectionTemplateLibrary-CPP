#pragma once

#include <string>
#include <type_traits>

namespace rtl {

    constexpr const char* NAMESPACE_GLOBAL = "namespace_global";


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


    namespace access 
    {
        //Allocation type.
        enum class alloc
        {
            None = -1,
            Stack = 0,
            Heap = 1,
        };
    }


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
        static const std::string dctor(const std::string& pRecordName) {
            return (pRecordName + "::~" + pRecordName + "()");
        }

        static const std::string ctor(const std::string& pRecordName) {
            return (pRecordName + "::" + pRecordName + "()");
        }

        static const std::string copyCtor(const std::string& pRecordName) {
            return (pRecordName + "::" + pRecordName + "(const " + pRecordName + "&)");
        }
    };
}