#pragma once

#include <type_traits>

namespace rtl {

    enum class Type { NONE = 0 };

    constexpr const char* CTOR_SUFFIX = "::ctor";
    constexpr const char* NAMESPACE_GLOBAL = "namespace_global";

#define GETTER(_type, _name, _var)                        \
    inline constexpr const _type& get##_name() const {    \
        return _var;                                      \
    }

#define GETTER_STATIC_REF(_type, _name, _var)           \
    inline static _type& get##_name() {                 \
        return _var;                                    \
    }

#define GETTER_STATIC_CONST_REF(_type, _name, _var)         \
    inline static constexpr const _type& get##_name() {     \
        return _var;                                        \
    }

    template<class _typeA, class _typeB>
    using enable_if_same = typename std::enable_if< std::is_same<_typeA, _typeB>::value >::type;

    template<class _typeA, class _typeB>
    using enable_if_notSame = typename std::enable_if< !std::is_same<_typeA, _typeB>::value >::type;
}