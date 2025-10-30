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

#include "Function.h"
#include "ReflectionBuilder.h"

namespace rtl::builder 
{
    struct CtorBuilder : protected detail::ReflectionBuilder
    {
        CtorBuilder(const std::string_view pNamespace, const std::string_view pRecord, 
                    const std::string_view pFunction, std::size_t pRecordId);

        template<class _recordType, class ..._signature>
        const Function build() const;
    };


/*  @struct: Builder<detail::member, args...>
    @param: specialized with member,
    *   member::NonConst - provides interface to register member funtion.
    *   member::Const - provides interface to register const-member funtions.
    *   member::Static - provides interface to register static member funtions.
    *   member::None - provides interface to register non-member funtions.
    @param: 
    *   _signature: arguments types of functions pointers or constructors (auto-deduced/explicitly-specified).
    * provides interface to register all sort of functions, methods & constructors.
    * every specialization has a 'build()' function, which accepts a function pointer.
    * function pointer can be non-member or member(static/const/non-const) functions.
*/  template<detail::member _typeQ, class ..._signature>
    struct Builder;
}


namespace rtl::builder
{
/*  @struct: Builder<detail::member::None, void>
    * specialized specifically to register overloaded non-member & static member functions with no arguments.
    * Objects of this class will be created & returned by the function,
    *   - type::function<void>(..)
    * with template parameter is only 'void', explicitly specified.
*/  template<>
    struct Builder<detail::member::None, void> : protected detail::ReflectionBuilder
    {
        Builder(std::size_t pRecordId, const std::string_view pFunction,
                const std::string_view pNamespace);

        template<class _returnType>
        const Function build(_returnType(*pFunctor)()) const;
    };


/*  @struct: Builder<detail::member::None, _signature...>
    * specialized specifically to register overloaded non-member  & static member functions with any arguments.
    * Objects of this class will be created & returned by the function,
    *   - type::function<...>(..)
    * with template parameters can be anything, explicitly specified.
*/  template<class ..._signature>
    struct Builder<detail::member::None, _signature...> : protected detail::ReflectionBuilder
    {
        Builder(std::size_t pRecordId, const std::string_view pFunction,
                const std::string_view pNamespace);

        template<class _returnType>
        const Function build(_returnType(*pFunctor)(_signature...)) const;
    };


/*  @struct: Builder<detail::member::None>
    * specialized specifically to register non-member functions with any signature and with no overloads.
    * Objects of this class will be created & returned by the function,
    *   - type::function(..)
    * with no template parameters specified.
*/  template<>
    struct Builder<detail::member::None> : protected detail::ReflectionBuilder
    {
        Builder(std::size_t pRecordId, const std::string_view pFunction,
                const std::string_view pNamespace);

        template<class _returnType, class ..._signature>
        const Function build(_returnType(*pFunctor)(_signature...)) const;
    };
}


namespace rtl::builder
{
/*  @struct: Builder<detail::member::None, void>
    * specialized specifically to register overloaded non-member & static member functions with no arguments.
    * Objects of this class will be created & returned by the function,
    *   - RecordBuilder<_recordType>::methodStatic<void>(..)
    * with template parameter is only 'void', explicitly specified.
*/  template<>
    struct Builder<detail::member::Static, void> : protected detail::ReflectionBuilder
    {
        traits::uid_t m_recordUid;

        Builder(traits::uid_t pRecordUid, const std::string_view pFunction,
                std::size_t pRecordId, const std::string_view pNamespace);

        template<class _returnType>
        const Function build(_returnType(*pFunctor)()) const;
    };


/*  @struct: Builder<detail::member::None, _signature...>
    * specialized specifically to register overloaded non-member  & static member functions with any arguments.
    * Objects of this class will be created & returned by the function,
    *   - RecordBuilder<_recordType>::methodStatic<...>(..)
    * with template parameters can be anything, explicitly specified.
*/  template<class ..._signature>
    struct Builder<detail::member::Static, _signature...> : protected detail::ReflectionBuilder
    {
        traits::uid_t m_recordUid;

        Builder(traits::uid_t pRecordUid, const std::string_view pFunction,
                std::size_t pRecordId, const std::string_view pNamespace);

        template<class _returnType>
        const Function build(_returnType(*pFunctor)(_signature...)) const;
    };


/*  @struct: Builder<detail::member::None>
    * specialized specifically to register non-member functions with any signature and with no overloads.
    * Objects of this class will be created & returned by the function,
    *   - RecordBuilder<_recordType>::methodStatic(..)
    * with no template parameters specified.
*/  template<>
    struct Builder<detail::member::Static> : protected detail::ReflectionBuilder
    {
        traits::uid_t m_recordUid;

        Builder(traits::uid_t pRecordUid, const std::string_view pFunction,
                std::size_t pRecordId, const std::string_view pNamespace);

        template<class _returnType, class ..._signature>
        const Function build(_returnType(*pFunctor)(_signature...)) const;
    };
}


namespace rtl::builder
{
/*  @struct: Builder<detail::member::Const, void>
    * specialized specifically to register overloaded const-member-functions with no arguments.
    * Objects of this class will be created & returned by function,
    *   - RecordBuilder<_recordType>::methodConst<void>(..)
    * with template parameters is only 'void' explicitly specified.
*/  template<>
    struct Builder<detail::member::Const, void> : protected detail::ReflectionBuilder
    {
        Builder(const std::string_view pFunction, std::size_t pRecordId);

        template<class _recordType, class _returnType>
        const Function build(_returnType(_recordType::* pFunctor)() const) const;
    };


/*  @struct: Builder<detail::member::Const, _signature...>
    * specialized specifically to register overloaded const-member-functions with any arguments.
    * Objects of this class will be created & returned by function,
    *   - RecordBuilder<_recordType>::methodConst<...>(..)
    * with template parameters can be anything, explicitly specified.
*/  template<class ..._signature>
    struct Builder<detail::member::Const, _signature...> : protected detail::ReflectionBuilder
    {
        Builder(const std::string_view pFunction, std::size_t pRecordId);

        template<class _recordType, class _returnType>
        const Function build(_returnType(_recordType::* pFunctor)(_signature...) const) const;
    };


/*  @struct: Builder<detail::member::Const>
    * specialized specifically to register non-overloaded const-member-functions with any arguments.
    * Objects of this class will be created & returned by function,
    *   - RecordBuilder<_recordType>::methodConst()
    * with no template parameters specified.
*/  template<>
    struct Builder<detail::member::Const> : protected detail::ReflectionBuilder
    {
        Builder(const std::string_view pFunction, std::size_t pRecordId);

        template<class _recordType, class _returnType, class ..._signature>
        const Function build(_returnType(_recordType::* pFunctor)(_signature...) const) const;
    };
}


namespace rtl::builder 
{
/*  @struct: Builder<detail::member::NonConst, void>
    * specialized specifically to register overloaded non-const-member-functions with no arguments.
    * Objects of this class will be created & returned by function,
    *   - RecordBuilder<_recordType>::method<void>(..)
    * with template parameters is only 'void' explicitly specified.
*/  template<>
    struct Builder<detail::member::NonConst, void> : protected detail::ReflectionBuilder
    {
        Builder(const std::string_view pFunction, std::size_t pRecordId);

        template<class _recordType, class _returnType>
        const Function build(_returnType(_recordType::* pFunctor)()) const;
    };


/*  @struct: Builder<detail::member::NonConst, _signature...>
    * specialized specifically to register overloaded non-const-member-functions with no arguments.
    * Objects of this class will be created & returned by function,
    *   - RecordBuilder<_recordType>::method<void>(..)
    * with template parameters is only 'void' explicitly specified.
*/  template<class ..._signature>
    struct Builder<detail::member::NonConst, _signature...> : protected detail::ReflectionBuilder
    {
        Builder(const std::string_view pFunction, std::size_t pRecordId);

        template<class _recordType, class _returnType>
        const Function build(_returnType(_recordType::* pFunctor)(_signature...)) const;
    };


/*  @struct: Builder<detail::member::NonConst>
    * specialized specifically to register non-overloaded non-const-member-functions and constructors with any arguments.
    * Objects of this class will be created & returned by function,
    *   - RecordBuilder<_recordType>::method() - with no template parameters specified.
    *   - RecordBuilder<_recordType>::constructor<...>() - template parameters can be anything or none, explicitly specified.
*/  template<>
    struct Builder<detail::member::NonConst> : protected detail::ReflectionBuilder
    {
        Builder(const std::string_view pFunction, std::size_t pRecordId);

        template<class _recordType, class _returnType, class ..._signature>
        const Function build(_returnType(_recordType::* pFunctor)(_signature...)) const;
    };
}