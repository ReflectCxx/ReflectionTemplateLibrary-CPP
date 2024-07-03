#pragma once

#include <type_traits>

namespace rtl {

    //Type Qualifier
    enum class typeQ
    {
        Vol,     //Volatile
        Const,  //Const
    };

    enum class Type { NONE = 0 };

    constexpr const char* CTOR_SUFFIX = "::ctor";
    constexpr const char* NAMESPACE_GLOBAL = "namespace_global";

#define GETTER(_varType, _name, _var, _getType)                 \
    inline constexpr const _varType& get##_name() _getType {    \
        return _var;                                            \
    }

#define GETTER_REF(_varType, _name, _var)       \
    inline _varType& get##_name() {             \
        return _var;                            \
    }

    template<class _typeA, class _typeB>
    using enable_if_same = typename std::enable_if< std::is_same<_typeA, _typeB>::value >::type;

    template<class _typeA, class _typeB>
    using enable_if_notSame = typename std::enable_if< !std::is_same<_typeA, _typeB>::value >::type;
}