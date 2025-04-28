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

#define GETTER_BOOL(_name, _var)                        \
    inline const bool is##_name() const {     \
        return _var;                                    \
    }

    enum FunctorIdx
    {
        ZERO = 0,   //heap constructor index
		ONE,    //destructor index
        TWO
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
            Stack = 0,  //false
            Heap = 1,   //true
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
		InvalidAllocType,
        SignatureMismatch,
        InstanceTypeMismatch,
        InstanceConstMismatch,
        ConstructorNotFound,
        CopyConstructorNotFound,
        ConstCopyConstructorNotFound
    };


    struct CtorName
    {
        static const std::string dctor(const std::string& pRecordName) {
            return (pRecordName + "::~" + pRecordName + "()");
        }

        static const std::string ctor(const std::string& pRecordName) {
            return (pRecordName + "::" + pRecordName + "()");
        }

        static const std::string copy(const std::string& pRecordName) {
            return (pRecordName + "::" + pRecordName + "(" + pRecordName + "&)");
        }

        static const std::string constCopy(const std::string& pRecordName) {
            return (pRecordName + "::" + pRecordName + "(const " + pRecordName + "&)");
        }
    };
}