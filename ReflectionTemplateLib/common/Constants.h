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

    template<class _typeA, class _typeB>
    using enable_if_same = typename std::enable_if< std::is_same<_typeA, _typeB>::value >::type;

    template<class _typeA, class _typeB>
    using enable_if_notSame = typename std::enable_if< !std::is_same<_typeA, _typeB>::value >::type;

    template<class _returnType, class ..._signature>
    using Functor = _returnType(*)(_signature...);

    template<class _recordType, class _returnType, class ..._signature>
    using MethodPtr = _returnType(_recordType:: *)(_signature...);

    template<class _recordType, class _returnType, class ..._signature>
    using MethodPtrConst = _returnType(_recordType::*)(_signature...) const;
}