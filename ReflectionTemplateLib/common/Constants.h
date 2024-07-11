#pragma once

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
        CopyConstructorNotFound
    };


    struct Ctor {
        static constexpr const char* CTOR = "::ctor()";
        static constexpr const char* DCTOR = "::~dctor()";
        static constexpr const char* CTOR_COPY = "::ctor(&)";
        static constexpr const char* CTOR_CONST_COPY = "::ctor(const&)";
    };

    constexpr const char* NAMESPACE_GLOBAL = "namespace_global";

#define GETTER(_varType, _name, _var)                       \
    inline constexpr const _varType& get##_name() const {   \
        return _var;                                        \
    }

#define GETTER_REF(_varType, _name, _var)       \
    inline _varType& get##_name() const {       \
        return _var;                            \
    }

    template<class _type>
    using enable_if_void = typename std::enable_if< std::is_same<_type, void>::value >::type;

    template<class _type>
    using enable_if_non_void = typename std::enable_if< !std::is_same<_type, void>::value >::type;

    template<class _typeA, class _typeB>
    using enable_if_same = typename std::enable_if< std::is_same<_typeA, _typeB>::value >::type;

    template<class _type, class _typeB>
    using enable_if_not_same = typename std::enable_if< !std::is_same<_type, _typeB>::value >::type;
}