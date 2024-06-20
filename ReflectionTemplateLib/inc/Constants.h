#pragma once

#include <type_traits>

namespace rtl {

    const char* const NS_GLOBAL = "namespace_global";
    const char* const CTOR_SUFFIX = "::ctor::";

#define GETTER(_type, _name, _var)                        \
    inline constexpr const _type& get##_name() const {    \
        return _var;                                      \
    }

    template<class _typeA, class _typeB>
    using enable_if_same = typename std::enable_if< std::is_same<_typeA, _typeB>::value >::type;

    template<class _typeA, class _typeB>
    using enable_if_notSame = typename std::enable_if< !std::is_same<_typeA, _typeB>::value >::type;
}