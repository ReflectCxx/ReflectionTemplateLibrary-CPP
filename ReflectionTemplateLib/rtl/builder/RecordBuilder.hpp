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
    template<class _recordType>
    inline RecordBuilder<_recordType>::RecordBuilder(const std::string_view pNamespace, const std::string_view pRecord, std::size_t pRecordId)
        : m_record(pRecord)
        , m_namespace(pNamespace)
        , m_recordId(pRecordId) 
    { }

    template<class _recordType>
    inline const Function RecordBuilder<_recordType>::build() const
    {
        return ConstructorBuilder<_recordType>(m_namespace, m_record).build();
    }
}


namespace rtl::builder 
{
/*  @method: constructor<...>()
    @param: none
    @return: ConstructorBuilder<_recordType, _signature...>
    * the copy constructors params are detected at compile time only.
    * template params <...> - any combination of parameters.
*/  template<class _recordType>
    template<class ..._signature>
    inline constexpr const ConstructorBuilder<_recordType, traits::remove_cref_t<_signature>...> MethodBuilder<_recordType>::constructor() const
    {
        constexpr bool isDefaultCtor = (sizeof...(_signature) == 0);
        constexpr bool isCopyOrMoveCtor = (sizeof...(_signature) == 1 && traits::is_first_type_same_v<_recordType, _signature...>);
        constexpr bool isDeclearedCtor = rtl::traits::has_constructor<_recordType, _signature...>;

        static_assert(!isDefaultCtor, "Default-constructor registration detected! It is implicitly registered with the Type.");
        static_assert(!isCopyOrMoveCtor, "Copy/Move-constructor registration detected! It is implicitly registered with the Type.");
        static_assert(isDeclearedCtor, "Constructor with given signature is not valid or declearation not found.");

        return ConstructorBuilder<_recordType, traits::remove_cref_t<_signature>...>();
    }


/*  @method: methodStatic()
    @param: std::string, name of function as string.
    @return: Builder<detail::member::Static, _signature...>
    * registers only static member functions.
    * used for registering unique static member function, if overload exists, use templated version 'methodStatic<...>()'.
    * the 'build(..)' called on return object will accepts static member function pointer only.
    * compiler error on 'build(..)' if non-static member or non-member function pointer is passed.
*/  template<class _recordType>
    inline const Builder<detail::member::Static> MethodBuilder<_recordType>::methodStatic(const std::string_view pFunction) const
    {
        return Builder<detail::member::Static>(detail::TypeId<_recordType>::get(), pFunction, "");
    }


/*  @method: methodStatic<...>()
    @param: std::string, name of function as string.
    @return: Builder<detail::member::Static, _signature...>
    * registers only static member functions.
    * used for registering overloads, if unique member function, use non-templated version 'methodStatic()'.
    * template parameters must be explicitly specified, should be exactly same as the member-function being registered.
    * the 'build(..)' called on return object will accepts static member function pointer only.
    * compiler error on 'build(..)' if const member or non-member function pointer is passed.
*/  template<class _recordType>
    template<class ..._signature>
    inline const Builder<detail::member::Static, _signature...> MethodBuilder<_recordType>::methodStatic(const std::string_view pFunction) const
    {
        return Builder<detail::member::Static, _signature...>(detail::TypeId<_recordType>::get(), pFunction, "");
    }


/*  @method: method()
    @param: std::string, name of function as string.
    @return: Builder<detail::member::NonConst>
    * registers non-const, non-static member functions.
    * the 'build(..)' called on return object will accepts non-const, non-static member-function-pointer only.
    * compiler error on 'build(..)' if const, static member or non-member function pointer is passed.
*/  template<class _recordType>
    inline const Builder<detail::member::NonConst> MethodBuilder<_recordType>::method(const std::string_view pFunction) const
    {
        return Builder<detail::member::NonConst>(pFunction, detail::TypeId<_recordType>::get());
    }


/*  @method: methodConst()
    @param: std::string, name of function as string.
    @return: Builder<detail::member::Const>
    * registers const member functions.
    * used for registering unique member function, if overload exists, use templated version 'methodConst<...>()'.
    * template parameters must be explicitly specified, should be exactly same as the member-function being registered.
    * the 'build(..)' called on return object will accepts non-const member-function-pointer only.
    * compiler error 'build(..)' if non-const, static member or non-member function pointer is passed.
*/  template<class _recordType>
    inline const Builder<detail::member::Const> MethodBuilder<_recordType>::methodConst(const std::string_view pFunction) const
    {
        return Builder<detail::member::Const>(pFunction, detail::TypeId<_recordType>::get());
    }


/*  @method: method()
    @param: std::string, name of function as string.
    @return: Builder<detail::member::NonConst, _signature...>
    * registers non-const member functions.
    * used for registering overloads, for unique member function, use non-templated version 'method()'.
    * template parameters must be explicitly specified, should be exactly same as the member-function being registered.
    * the 'build(..)' called on return object will accepts non-const member-function-pointer only.
    * compiler error on 'build(..)' if const, static member or non-member function pointer is passed.
*/  template<class _recordType>
    template<class ..._signature>
    inline const Builder<detail::member::NonConst, _signature...> MethodBuilder<_recordType>::method(const std::string_view pFunction) const
    {
        return Builder<detail::member::NonConst, _signature...>(pFunction, detail::TypeId<_recordType>::get());
    }


/*  @method: methodConst<...>()
    @param: std::string, name of function as string.
    @return: Builder<detail::member::Const, _signature...>
    * registers const member functions.
    * used for registering overloads, for unique member function, use non-templated version 'methodConst()'.
    * template parameters must be explicitly specified, should be exactly same as the member-function being registered.
    * the 'build(..)' called on return object will accepts const member-function-pointer only.
    * compiler error on 'build(..)' if non-const, static member or non-member function pointer is passed.
*/  template<class _recordType>
    template<class ..._signature>
    inline const Builder<detail::member::Const, _signature...> MethodBuilder<_recordType>::methodConst(const std::string_view pFunction) const
    {
        return Builder<detail::member::Const, _signature...>(pFunction, detail::TypeId<_recordType>::get());
    }
}