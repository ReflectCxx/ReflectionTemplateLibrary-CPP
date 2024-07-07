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

    constexpr const char* CTOR_SUFFIX = "::ctor";
    constexpr const char* NAMESPACE_GLOBAL = "namespace_global";

#define GETTER(_varType, _name, _var)                       \
    inline constexpr const _varType& get##_name() const {   \
        return _var;                                        \
    }

#define GETTER_REF(_varType, _name, _var)       \
    inline _varType& get##_name() {             \
        return _var;                            \
    }

    template<class _type>
    using enable_if_void = typename std::enable_if< std::is_same<_type, void>::value >::type;

    template<class _type>
    using enable_if_non_void = typename std::enable_if< !std::is_same<_type, void>::value >::type;
}