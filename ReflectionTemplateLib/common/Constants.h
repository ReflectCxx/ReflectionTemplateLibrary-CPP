#pragma once

#include <string>
#include <type_traits>

namespace rtl {

    constexpr const char* NAMESPACE_GLOBAL = "namespace_global";

#define GETTER(_varType, _name, _var)                       \
    inline constexpr const _varType& get##_name() const {   \
        return _var;                                        \
    }


#define GETTER_REF(_varType, _name, _var)       \
    inline _varType& get##_name() const {       \
        return _var;                            \
    }


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
            None,
            Heap,
            Stack
        };
    }

    //Qualifier type.
    enum class ConstructorType
    {
        None,
        Ctor,
        Copy,
        ConstCopy
    };


    enum class Error
    {
        None,
        EmptyInstance,
        SignatureMismatch,
        InstanceTypeMismatch,
        InstanceConstMismatch,
        ConstructorNotFound,
        CopyConstructorNotFound,
        ConstCopyConstructorNotFound
    };


    template<access::alloc _alloc>
    struct CtorName
    {
        static const std::string ctor(const std::string& pRecordName) {
            if constexpr (_alloc == access::alloc::Heap) {
                return ("new " + pRecordName + "::" + pRecordName + "()");
            }
            else if constexpr (_alloc == access::alloc::Stack) {
                return (pRecordName + "::" + pRecordName + "()");
            }
        }

        static const std::string copy(const std::string& pRecordName) {
            if constexpr (_alloc == access::alloc::Heap) {
                return ("new " + pRecordName + "::" + pRecordName + "(" + pRecordName + "&)");
            }
            else if constexpr (_alloc == access::alloc::Stack) {
                return (pRecordName + "::" + pRecordName + "(" + pRecordName + "&)");
            }
        }

        static const std::string constCopy(const std::string& pRecordName) {
            if constexpr (_alloc == access::alloc::Heap) {
                return ("new " + pRecordName + "::" + pRecordName + "(const " + pRecordName + "&)");
            }
            else if constexpr (_alloc == access::alloc::Stack) {
                return (pRecordName + "::" + pRecordName + "(const " + pRecordName + "&)");
            }
        }
    };

    template<>
    struct  CtorName<access::alloc::None>
    {
        static const std::string dctor(const std::string& pRecordName) {
            return (pRecordName + "::~" + pRecordName + "()");
        }
    };
}