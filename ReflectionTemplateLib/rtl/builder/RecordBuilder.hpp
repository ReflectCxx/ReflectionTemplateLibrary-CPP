/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                         *
 *                                                                       *
 *************************************************************************/


#pragma once

#include "rtl_traits.h"
#include "RecordBuilder.h"
#include "ConstructorBuilder.h"

namespace rtl::builder 
{
    template<class record_t>
    inline RecordBuilder<record_t>::RecordBuilder(const std::string& pNamespace, const std::string& pRecord, traits::uid_t pRecordId)
        : m_recordStr(pRecord)
        , m_namespaceStr(pNamespace)
        , m_recordId(pRecordId) 
    { }

    template<class record_t>
    inline const Function RecordBuilder<record_t>::build() const
    {
        return ConstructorBuilder<record_t>(m_namespaceStr, m_recordStr).build();
    }
}


namespace rtl::builder 
{
/*  @method: constructor<...>()
    @param: none
    @return: ConstructorBuilder<record_t, signature_t...>
    * the copy constructors params are detected at compile time only.
    * template params <...> - any combination of parameters.
*/  template<class record_t>
    template<class ...signature_t>
    inline constexpr const ConstructorBuilder<record_t, signature_t...> MethodBuilder<record_t>::constructor() const
    {
        constexpr bool isDefaultCtor = (sizeof...(signature_t) == 0);
        constexpr bool isCopyOrMoveCtor = (sizeof...(signature_t) == 1 && traits::is_first_type_same_v<record_t, signature_t...>);
        constexpr bool isDeclearedCtor = rtl::traits::has_constructor<record_t, signature_t...>;

        static_assert(!isDefaultCtor, "Default-constructor registration detected! It is implicitly registered with the Type.");
        static_assert(!isCopyOrMoveCtor, "Copy/Move-constructor registration detected! It is implicitly registered with the Type.");
        static_assert(isDeclearedCtor, "Constructor with given signature is not valid or declearation not found.");

        return ConstructorBuilder<record_t, signature_t...>();
    }


/*  @method: methodStatic()
    @param: std::string, name of function as string.
    @return: Builder<detail::member::Static, signature_t...>
    * registers only static member functions.
    * used for registering unique static member function, if overload exists, use templated version 'methodStatic<...>()'.
    * the 'build(..)' called on return object will accepts static member function pointer only.
    * compiler error on 'build(..)' if non-static member or non-member function pointer is passed.
*/  template<class record_t>
    inline const Builder<detail::member::Static> MethodBuilder<record_t>::methodStatic(const std::string& pFunction) const
    {
        return Builder<detail::member::Static>(traits::uid<record_t>::value, pFunction, detail::INIT_LATER, detail::INIT_LATER);
    }


/*  @method: methodStatic<...>()
    @param: std::string, name of function as string.
    @return: Builder<detail::member::Static, signature_t...>
    * registers only static member functions.
    * used for registering overloads, if unique member function, use non-templated version 'methodStatic()'.
    * template parameters must be explicitly specified, should be exactly same as the member-function being registered.
    * the 'build(..)' called on return object will accepts static member function pointer only.
    * compiler error on 'build(..)' if const member or non-member function pointer is passed.
*/  template<class record_t>
    template<class ...signature_t>
    inline const Builder<detail::member::Static, signature_t...> MethodBuilder<record_t>::methodStatic(const std::string& pFunction) const
    {
        return Builder<detail::member::Static, signature_t...>(traits::uid<record_t>::value, pFunction, detail::INIT_LATER, detail::INIT_LATER);
    }


/*  @method: method()
    @param: std::string, name of function as string.
    @return: Builder<detail::member::NonConst>
    * registers non-const, non-static member functions.
    * the 'build(..)' called on return object will accepts non-const, non-static member-function-pointer only.
    * compiler error on 'build(..)' if const, static member or non-member function pointer is passed.
*/  template<class record_t>
    inline const Builder<detail::member::NonConst> MethodBuilder<record_t>::method(const std::string& pFunction) const
    {
        return Builder<detail::member::NonConst>(pFunction, traits::uid<record_t>::value);
    }


/*  @method: methodConst()
    @param: std::string, name of function as string.
    @return: Builder<detail::member::Const>
    * registers const member functions.
    * used for registering unique member function, if overload exists, use templated version 'methodConst<...>()'.
    * template parameters must be explicitly specified, should be exactly same as the member-function being registered.
    * the 'build(..)' called on return object will accepts non-const member-function-pointer only.
    * compiler error 'build(..)' if non-const, static member or non-member function pointer is passed.
*/  template<class record_t>
    inline const Builder<detail::member::Const> MethodBuilder<record_t>::methodConst(const std::string& pFunction) const
    {
        return Builder<detail::member::Const>(pFunction, traits::uid<record_t>::value);
    }


/*  @method: method()
    @param: std::string, name of function as string.
    @return: Builder<detail::member::NonConst, signature_t...>
    * registers non-const member functions.
    * used for registering overloads, for unique member function, use non-templated version 'method()'.
    * template parameters must be explicitly specified, should be exactly same as the member-function being registered.
    * the 'build(..)' called on return object will accepts non-const member-function-pointer only.
    * compiler error on 'build(..)' if const, static member or non-member function pointer is passed.
*/  template<class record_t>
    template<class ...signature_t>
    inline const Builder<detail::member::NonConst, signature_t...> MethodBuilder<record_t>::method(const std::string& pFunction) const
    {
        return Builder<detail::member::NonConst, signature_t...>(pFunction, traits::uid<record_t>::value);
    }


/*  @method: methodConst<...>()
    @param: std::string, name of function as string.
    @return: Builder<detail::member::Const, signature_t...>
    * registers const member functions.
    * used for registering overloads, for unique member function, use non-templated version 'methodConst()'.
    * template parameters must be explicitly specified, should be exactly same as the member-function being registered.
    * the 'build(..)' called on return object will accepts const member-function-pointer only.
    * compiler error on 'build(..)' if non-const, static member or non-member function pointer is passed.
*/  template<class record_t>
    template<class ...signature_t>
    inline const Builder<detail::member::Const, signature_t...> MethodBuilder<record_t>::methodConst(const std::string& pFunction) const
    {
        return Builder<detail::member::Const, signature_t...>(pFunction, traits::uid<record_t>::value);
    }
}