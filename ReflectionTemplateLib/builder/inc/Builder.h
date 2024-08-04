#pragma once

#include "Function.h"
#include "ReflectionBuilder.hpp"

namespace rtl {

    namespace builder
    {
    /*  @struct: Builder<TypeQ, args...>
        @param: specialized with TypeQ,
        *   TypeQ::Mute - provides interface to register member funtion.
        *   TypeQ::Const - provides interface to register const-member funtions.
        *   TypeQ::None - provides interface to register non-member and static member funtions.
        @param: 
        *   _signature: arguments types of functions pointers or constructors (auto deduced/explicitly specified).
        * provides interface to register all sort of functions, methods & constructors.
        * every specialization has a 'build()' function, which accepts a function pointer.
        * function pointer can be non-member or member(static/const/non-const) functions.
    */  template<TypeQ _typeQ, class ..._signature>
        struct Builder;
    }


    namespace builder
    {
    /*  @struct: Builder<TypeQ::None, void>
        * specialized specifically to register overloaded non-member & static member functions with no arguments.
        * Objects of this class will be created & returned by these functions,
        *   - Reflect::function<void>(..)
        *   - RecordBuilder<_recordType>::methodStatic<void>(..)
        * with template parameter is only 'void', explicitly specified.
    */  template<>
        struct Builder<TypeQ::None, void> : protected detail::ReflectionBuilder
        {
            Builder(const std::string& pNamespace, const std::string& pRecord,
                    const std::string& pFunction);

            template<class _returnType>
            constexpr const access::Function build(_returnType(*pFunctor)()) const;
        };


    /*  @struct: Builder<TypeQ::None, _signature...>
        * specialized specifically to register overloaded non-member  & static member functions with any arguments.
        * Objects of this class will be created & returned by these functions,
        *   - Reflect::function<...>(..)
        *   - RecordBuilder<_recordType>::methodStatic<...>(..)
        * with template parameters can be anything, explicitly specified.
    */  template<class ..._signature>
        struct Builder<TypeQ::None, _signature...> : protected detail::ReflectionBuilder
        {
            Builder(const std::string& pNamespace, const std::string& pRecord,
                    const std::string& pFunction);

            template<class _returnType>
            constexpr const access::Function build(_returnType(*pFunctor)(_signature...)) const;
        };


    /*  @struct: Builder<TypeQ::None>
        * specialized specifically to register non-member functions with any signature and with no overloads.
        * Objects of this class will be created & returned by these functions,
        *   - Reflect::function(..)
        *   - RecordBuilder<_recordType>::methodStatic(..)
        * with no template parameters specified.
    */  template<>
        struct Builder<TypeQ::None> : protected detail::ReflectionBuilder
        {
            Builder(const std::string& pNamespace, const std::string& pRecord,
                    const std::string& pFunction);

            template<class _returnType, class ..._signature>
            constexpr const access::Function build(_returnType(*pFunctor)(_signature...)) const;
        };
    }


    namespace builder
    {
    /*  @struct: Builder<TypeQ::Const, void>
        * specialized specifically to register overloaded const-member-functions with no arguments.
        * Objects of this class will be created & returned by function,
        *   - RecordBuilder<_recordType>::methodConst<void>(..)
        * with template parameters is only 'void' explicitly specified.
    */  template<>
        struct Builder<TypeQ::Const, void> : protected detail::ReflectionBuilder
        {
            Builder(const std::string& pNamespace, const std::string& pRecord,
                    const std::string& pFunction);

            template<class _recordType, class _returnType>
            constexpr const access::Function build(_returnType(_recordType::* pFunctor)() const) const;
        };


    /*  @struct: Builder<TypeQ::Const, _signature...>
        * specialized specifically to register overloaded const-member-functions with any arguments.
        * Objects of this class will be created & returned by function,
        *   - RecordBuilder<_recordType>::methodConst<...>(..)
        * with template parameters can be anything, explicitly specified.
    */  template<class ..._signature>
        struct Builder<TypeQ::Const, _signature...> : protected detail::ReflectionBuilder
        {
            Builder(const std::string& pNamespace, const std::string& pRecord,
                    const std::string& pFunction);

            template<class _recordType, class _returnType>
            constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...) const) const;
        };


    /*  @struct: Builder<TypeQ::Const>
        * specialized specifically to register non-overloaded const-member-functions with any arguments.
        * Objects of this class will be created & returned by function,
        *   - RecordBuilder<_recordType>::methodConst()
        * with no template parameters specified.
    */  template<>
        struct Builder<TypeQ::Const> : protected detail::ReflectionBuilder
        {
            Builder(const std::string& pNamespace, const std::string& pRecord,
                    const std::string& pFunction);

            template<class _recordType, class _returnType, class ..._signature>
            constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...) const) const;
        };
    }


    namespace builder 
    {
    /*  @struct: Builder<TypeQ::Mute, void>
        * specialized specifically to register overloaded non-const-member-functions with no arguments.
        * Objects of this class will be created & returned by function,
        *   - RecordBuilder<_recordType>::method<void>(..)
        * with template parameters is only 'void' explicitly specified.
    */  template<>
        struct Builder<TypeQ::Mute, void> : protected detail::ReflectionBuilder
        {
            Builder(const std::string& pNamespace, const std::string& pRecord,
                    const std::string& pFunction);

            template<class _recordType, class _returnType>
            constexpr const access::Function build(_returnType(_recordType::* pFunctor)()) const;
        };


    /*  @struct: Builder<TypeQ::Mute, _signature...>
        * specialized specifically to register overloaded non-const-member-functions with no arguments.
        * Objects of this class will be created & returned by function,
        *   - RecordBuilder<_recordType>::method<void>(..)
        * with template parameters is only 'void' explicitly specified.
    */  template<class ..._signature>
        struct Builder<TypeQ::Mute, _signature...> : protected detail::ReflectionBuilder
        {
            Builder(const std::string& pNamespace, const std::string& pRecord,
                    const std::string& pFunction);

            template<class _recordType, class _returnType>
            constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...)) const;
        };


    /*  @struct: Builder<TypeQ::Mute>
        * specialized specifically to register non-overloaded non-const-member-functions and constructors with any arguments.
        * Objects of this class will be created & returned by function,
        *   - RecordBuilder<_recordType>::method() - with no template parameters specified.
        *   - RecordBuilder<_recordType>::constructor<...>() - template parameters can be anything or none, explicitly specified.
    */  template<>
        struct Builder<TypeQ::Mute> : protected detail::ReflectionBuilder
        {
            Builder(const std::string& pNamespace, const std::string& pRecord,
                    const std::string& pFunction);

            template<class _recordType, class ..._signature>
            constexpr const access::Function build() const;

            template<class _recordType, class _returnType, class ..._signature>
            constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...)) const;
        };
    }
}