#pragma once

#include <string>
#include <type_traits>

namespace rtl {

    //Qualifier type.
    enum class TypeQ
    {
        None,
        Mute,   //Mutable
        Const,  //Constant
    };

    //Qualifier type.
    enum class FunctorType
    {
        None,
        Ctor,
        CopyCtor,
        CopyCtorConst,
        DCtor,
        Static,
        Method,
        Function
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

    constexpr const char* NAMESPACE_GLOBAL = "namespace_global";

    struct CtorName
    {
        static const std::string ctor(const std::string& pRecordName) {
            return (pRecordName + "::" + pRecordName + "()");
        }

        static const std::string dctor(const std::string& pRecordName) {
            return (pRecordName + "::~" + pRecordName + "()");
        }

        static const std::string copy(const std::string& pRecordName) {
            return (pRecordName + "::" + pRecordName + "(" + pRecordName + "&)");
        }

        static const std::string constCopy(const std::string& pRecordName) {
            return (pRecordName + "::" + pRecordName + "(const " + pRecordName + "&)");
        }
    };


#define GETTER(_varType, _name, _var)                       \
    inline constexpr const _varType& get##_name() const {   \
        return _var;                                        \
    }


#define GETTER_REF(_varType, _name, _var)       \
    inline _varType& get##_name() const {       \
        return _var;                            \
    }
}