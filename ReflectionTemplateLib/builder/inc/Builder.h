#pragma once

#include "Function.h"
#include "ReflectionBuilder.hpp"

namespace rtl {

    namespace builder
    {
    /*  Provides interface to register all sort of functions, methods & constructors.
        _signature: arguments types of the functions/constructors.
        _typeQ: Builder, specialized with TypeQ,
            TypeQ::None - provides interface to register non-member and static member funtions.
            TypeQ::Mute - provides interface to register member funtion.
            TypeQ::Const - provides interface to register const-member funtions.
        Every builder specialization has a 'build()' function, which takes function pointer as
        an argument which can be member(static/const)/non-member.
    */  template<TypeQ _typeQ, class ..._signature>
        struct Builder;
    }


    namespace builder
    {
    /*  specialized specifically to register overloaded non-member & static member functions with no arguments.
        Objects of this class will be created & returned by these functions,
            - Reflect::function<void>(..)
            - RecordBuilder<_recordType>::methodStatic<void>(..)
        with template parameter is only 'void', explicitly specified.
    */  template<>
        struct Builder<TypeQ::None, void> : protected detail::ReflectionBuilder
        {
            Builder(const std::string& pNamespace, const std::string& pRecord,
                    const std::string& pFunction);

            template<class _returnType>
            constexpr const access::Function build(_returnType(*pFunctor)()) const;
        };


    /*  specialized specifically to register overloaded non-member  & static member functions with any arguments.
        Objects of this class will be created & returned by these functions,
            - Reflect::function<...>(..)
            - RecordBuilder<_recordType>::methodStatic<...>(..)
        with template parameters can be anything, explicitly specified.
    */  template<class ..._signature>
        struct Builder<TypeQ::None, _signature...> : protected detail::ReflectionBuilder
        {
            Builder(const std::string& pNamespace, const std::string& pRecord,
                    const std::string& pFunction);

            template<class _returnType>
            constexpr const access::Function build(_returnType(*pFunctor)(_signature...)) const;
        };


    /*  specialized specifically to register non-member functions with any signature and with no overloads.
        Objects of this class will be created & returned by these functions,
            - Reflect::function(..)
            - RecordBuilder<_recordType>::methodStatic(..)
        with no template parameters specified.
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
    /*  specialized specifically to register overloaded const-member-functions with no arguments.
        Objects of this class will be created & returned by function,
            - RecordBuilder<_recordType>::methodConst<void>(..)
        with template parameters is only 'void' explicitly specified.
    */  template<>
        struct Builder<TypeQ::Const, void> : protected detail::ReflectionBuilder
        {
            Builder(const std::string& pNamespace, const std::string& pRecord,
                    const std::string& pFunction);

            template<class _recordType, class _returnType>
            constexpr const access::Function build(_returnType(_recordType::* pFunctor)() const) const;
		};


    /*  specialized specifically to register overloaded const-member-functions with any arguments.
        Objects of this class will be created & returned by function,
            - RecordBuilder<_recordType>::methodConst<...>(..)
        with template parameters can be anything, explicitly specified.
    */  template<class ..._signature>
        struct Builder<TypeQ::Const, _signature...> : protected detail::ReflectionBuilder
        {
            Builder(const std::string& pNamespace, const std::string& pRecord,
                    const std::string& pFunction);

            template<class _recordType, class _returnType>
            constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...) const) const;
        };


    /*  specialized specifically to register non-overloaded const-member-functions with any arguments.
        Objects of this class will be created & returned by function,
            - RecordBuilder<_recordType>::methodConst()
        with no template parameters specified.
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
    /*  specialized specifically to register overloaded non-const-member-functions with no arguments.
        Objects of this class will be created & returned by function,
            - RecordBuilder<_recordType>::method<void>(..)
        with template parameters is only 'void' explicitly specified.
    */  template<>
        struct Builder<TypeQ::Mute, void> : protected detail::ReflectionBuilder
        {
            Builder(const std::string& pNamespace, const std::string& pRecord,
                    const std::string& pFunction);

            template<class _recordType, class _returnType>
            constexpr const access::Function build(_returnType(_recordType::* pFunctor)()) const;
        };


    /*  specialized specifically to register overloaded non-const-member-functions with no arguments.
        Objects of this class will be created & returned by function,
            - RecordBuilder<_recordType>::method<void>(..)
        with template parameters is only 'void' explicitly specified.
    */  template<class ..._signature>
        struct Builder<TypeQ::Mute, _signature...> : protected detail::ReflectionBuilder
        {
            Builder(const std::string& pNamespace, const std::string& pRecord,
                    const std::string& pFunction);

            template<class _recordType, class _returnType>
            constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...)) const;
        };


    /*  specialized specifically to register non-overloaded non-const-member-functions and constructors with any arguments.
        Objects of this class will be created & returned by function,
            - RecordBuilder<_recordType>::method() - with no template parameters specified.
            - RecordBuilder<_recordType>::constructor<...>() - template parameters can be anything, explicitly specified.
    */  template<>
        struct Builder<TypeQ::Mute> : protected detail::ReflectionBuilder
        {
            Builder(const std::string& pNamespace, const std::string& pRecord,
                    const std::string& pFunction);

            template<class _recordType, class ..._signature>
            constexpr const access::Function
            build(enable_if_same<_recordType&, typename detail::TypeId<_signature...>::HEAD > *_= nullptr) const;

            template<class _recordType, class ..._signature>
            constexpr const access::Function
                build(enable_if_same<const _recordType&, typename detail::TypeId<_signature...>::HEAD > *_= nullptr) const;

            template<class _recordType, class ..._signature>
            constexpr const access::Function
                build(enable_if_not_same<_recordType&, typename detail::TypeId<_signature...>::HEAD > *_= nullptr,
                      enable_if_not_same<const _recordType&, typename detail::TypeId<_signature...>::HEAD > *__= nullptr) const;

            template<class _recordType, class _returnType, class ..._signature>
            constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...)) const;
        };
    }
}