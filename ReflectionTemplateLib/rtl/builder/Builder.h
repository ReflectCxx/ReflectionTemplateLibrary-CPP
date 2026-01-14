/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <inc/Function.h>
#include <builder/ReflectionBuilder.h>

namespace rtl::builder 
{
    struct CtorBuilder : protected ReflectionBuilder
    {
        CtorBuilder(const std::string& pNamespace, const std::string& pRecordStr,
                    const std::string& pFunction, traits::uid_t pRecordUid)
        : ReflectionBuilder(pFunction, pRecordUid, pRecordStr, pNamespace)
        { }

    /*  @method: build()
        @param: none
        @return: 'Function' object.
        * accepts no arguments, builds copy constructor which takes const object source.
        * called on object returned by 'RecordBuilder<record_t>::constructor<...>()'
        * template params <...>, explicitly specified.
        * calling with zero template params will build the default constructor ie, 'RecordBuilder<record_t>::constructor()'
    */  template<class record_t, class ...signature_t>
        const Function build() const
        {
            return buildConstructor<record_t, signature_t...>();
        }   
    };


/*  @struct: Builder<detail::member, args...>
    @param: specialized with member,
    *   member::NonConst - provides interface to register member funtion.
    *   member::Const - provides interface to register const-member funtions.
    *   member::Static - provides interface to register static member funtions.
    *   member::None - provides interface to register non-member funtions.
    @param: 
    *   signature_t: arguments types of functions pointers or constructors (auto-deduced/explicitly-specified).
    * provides interface to register all sort of functions, methods & constructors.
    * every specialization has a 'build()' function, which accepts a function pointer.
    * function pointer can be non-member or member(static/const/non-const) functions.
*/  template<detail::member, class ...>
    struct Builder;
}


namespace rtl::builder
{
    template<>
    struct Builder<detail::member::None, void> : protected ReflectionBuilder
    {
        Builder(traits::uid_t pRecordUid, const std::string& pFunction, const std::string& pNamespace)
        : ReflectionBuilder(pFunction, pRecordUid, detail::RECORD_NONE, pNamespace)
        { }

    /*  @method: build()
        @param: return_t(*)()
        @return: 'Function' object.
        * accepts a non-member or static-member function pointer with no arguments.
        * called on objects returned by 'type::function<void>(..)' & 'RecordBuilder<record_t>::methodStatic<void>(..)'
        * template param 'void' is explicitly specified.
    */  template<class return_t>
        const Function build(return_t(*pFunctor)()) const
        {
            return buildFunctor(pFunctor, detail::member::None);
        }
    };


    template<class ...signature_t>
    struct Builder<detail::member::None, signature_t...> : protected ReflectionBuilder
    {
        Builder(traits::uid_t pRecordUid, const std::string& pFunction, const std::string& pNamespace)
        : ReflectionBuilder(pFunction, pRecordUid, detail::RECORD_NONE, pNamespace)
        { }

    /*  @method: build()
        @param: return_t(*)(signature_t...)
        @return: 'Function' object.
        * it accepts a non-member or static-member function pointer.
        * called on objects returned by 'type::function<...>(..)' & 'RecordBuilder<record_t>::methodStatic<...>(..)'.
        * template params are explicitly specified.
    */  template<class return_t>
        const Function build(return_t(*pFunctor)(signature_t...)) const
        {
            return buildFunctor(pFunctor, detail::member::None);
        }
    };


    template<>
    struct Builder<detail::member::None> : protected ReflectionBuilder
    {
        Builder(traits::uid_t pRecordUid, const std::string& pFunction, const std::string& pNamespace)
        : ReflectionBuilder(pFunction, pRecordUid, detail::RECORD_NONE, pNamespace) 
        { }

    /*  @method: build()
        @param: return_t(*)(signature_t...)
        @return: 'Function' object.
        * accepts all non-member and static-member function pointer.
        * called on the objects returned by 'type::function()' & 'RecordBuilder<record_t>::methodStatic(..)'.
        * template params are auto deduced from the function pointer passed.
    */	template<class return_t, class ...signature_t>
        const Function build(return_t(*pFunctor)(signature_t...)) const
        {
            return buildFunctor(pFunctor, detail::member::None);
        }
    };
}


namespace rtl::builder
{
    template<>
    struct Builder<detail::member::Static, void> : protected ReflectionBuilder
    {
        Builder(traits::uid_t pRecordUid, const std::string& pFunction,
                const std::string& pRecordStr, const std::string& pNamespace) 
        : ReflectionBuilder(pFunction, pRecordUid, pRecordStr, pNamespace)
        { }

    /*  @method: build()
        @param: return_t(*)()
        @return: 'Function' object.
        * accepts a non-member or static-member function pointer with no arguments.
        * called on objects returned by 'type::function<void>(..)' & 'RecordBuilder<record_t>::methodStatic<void>(..)'
        * template param 'void' is explicitly specified.
    */  template<class return_t>
        const Function build(return_t(*pFunctor)()) const
        {
            return buildFunctor(pFunctor, detail::member::Static);
        }
    };


    template<class ...signature_t>
    struct Builder<detail::member::Static, signature_t...> : protected ReflectionBuilder
    {
        Builder(traits::uid_t pRecordUid, const std::string& pFunction,
                const std::string& pRecordStr, const std::string& pNamespace) 
        : ReflectionBuilder(pFunction, pRecordUid, pRecordStr, pNamespace)
        { }

    /*  @method: build()
        @param: return_t(*)(signature_t...)
        @return: 'Function' object.
        * it accepts a non-member or static-member function pointer.
        * called on objects returned by 'type::function<...>(..)' & 'RecordBuilder<record_t>::methodStatic<...>(..)'.
        * template params are explicitly specified.
    */  template<class return_t>
        inline const Function build(return_t(*pFunctor)(signature_t...)) const
        {
            return buildFunctor(pFunctor, detail::member::Static);
        }
    };

    
    template<>
    struct Builder<detail::member::Static> : protected ReflectionBuilder
    {
        Builder(traits::uid_t pRecordUid, const std::string& pFunction,
                const std::string& pRecordStr, const std::string& pNamespace)
        : ReflectionBuilder(pFunction, pRecordUid, pRecordStr, pNamespace)
        { }

    /*  @method: build()
        @param: return_t(*)(signature_t...)
        @return: 'Function' object.
        * accepts all non-member and static-member function pointer.
        * called on the objects returned by 'type::function()' & 'RecordBuilder<record_t>::methodStatic(..)'.
        * template params are auto deduced from the function pointer passed.
    */	template<class return_t, class ...signature_t>
        const Function build(return_t(*pFunctor)(signature_t...)) const
        {
            return buildFunctor(pFunctor, detail::member::Static);
        }
    };
}


namespace rtl::builder
{
    template<>
    struct Builder<detail::member::Const, void> : protected ReflectionBuilder
    {
        Builder(const std::string& pFunction, traits::uid_t pRecordUid) 
        : ReflectionBuilder(pFunction, pRecordUid, detail::INIT_LATER, detail::INIT_LATER)
        { }

    /*  @method: build()
        @param: return_t(record_t::*)() const.
        @return: 'Function' object.
        * accepts a const-member-function pointer with no arguments.
        * called on object returned by 'RecordBuilder<record_t>::methodConst<void>()'
        * template param 'void' is explicitly specified.
    */  template<class record_t, class return_t>
        const Function build(return_t(record_t::* pFunctor)() const) const
        {
            return buildMethodFunctor(pFunctor);
        }
    };

    
    template<class ...signature_t>
    struct Builder<detail::member::Const, signature_t...> : protected ReflectionBuilder
    {
        Builder(const std::string& pFunction, traits::uid_t pRecordUid) 
        : ReflectionBuilder(pFunction, pRecordUid, detail::INIT_LATER, detail::INIT_LATER)
        { }

    /*  @method: build()
        @param: return_t(record_t::*)(signature_t...) const.
        @return: 'Function' object.
        * accepts a const-member-function pointer with any arguments.
        * called on object returned by 'RecordBuilder<record_t>::methodConst<...>()'
        * template param are explicitly specified.
    */  template<class record_t, class return_t>
        const Function build(return_t(record_t::* pFunctor)(signature_t...) const) const
        {
            return buildMethodFunctor(pFunctor);
        }
    };

    
    template<>
    struct Builder<detail::member::Const> : protected ReflectionBuilder
    {
        Builder(const std::string& pFunction, traits::uid_t pRecordUid) 
        : ReflectionBuilder(pFunction, pRecordUid, detail::INIT_LATER, detail::INIT_LATER)
        { }

    /*  @method: build()
        @param: return_t(record_t::*)(signature_t...) const.
        @return: 'Function' object.
        * accepts function pointer of a const-member-function with any signature.
        * called on object returned by 'RecordBuilder<record_t>::methodConst()'
        * template params will be auto deduced from the function pointer passed.
    */  template<class record_t, class return_t, class ...signature_t>
        const Function build(return_t(record_t::* pFunctor)(signature_t...) const) const
        {
            return buildMethodFunctor(pFunctor);
        }
    };
}


namespace rtl::builder 
{
    template<>
    struct Builder<detail::member::NonConst, void> : protected ReflectionBuilder
    {
        Builder(const std::string& pFunction, traits::uid_t pRecordUid)
        : ReflectionBuilder(pFunction, pRecordUid, detail::INIT_LATER, detail::INIT_LATER)
        { }

    /*  @method: build()
        @param: return_t(record_t::*)()
        @return: 'Function' object.
        * accepts a non-const-member-function pointer with no arguments.
        * called on object returned by 'RecordBuilder<record_t>::method<void>()'
        * template param 'void' is explicitly specified.
    */  template<class record_t, class return_t>
        const Function build(return_t(record_t::* pFunctor)()) const
        {
            return buildMethodFunctor(pFunctor);
        }
    };


    template<class ...signature_t>
    struct Builder<detail::member::NonConst, signature_t...> : protected ReflectionBuilder
    {
        Builder(const std::string& pFunction, traits::uid_t pRecordUid)
        : ReflectionBuilder(pFunction, pRecordUid, detail::INIT_LATER, detail::INIT_LATER)
        { }

    /*  @method: build()
        @param: return_t(record_t::*)(signature_t...)
        @return: 'Function' object.
        * accepts a non-const-member-function pointer with any arguments.
        * called on object returned by 'RecordBuilder<record_t>::method<...>()'
        * template params are explicitly specified.
    */  template<class record_t, class return_t>
        const Function build(return_t(record_t::* pFunctor)(signature_t...)) const
        {
            return buildMethodFunctor(pFunctor);
        }
    };


    template<>
    struct Builder<detail::member::NonConst> : protected ReflectionBuilder
    {
        Builder(const std::string& pFunction, traits::uid_t pRecordUid) 
        : ReflectionBuilder(pFunction, pRecordUid, detail::INIT_LATER, detail::INIT_LATER)
        { }


    /*  @method: build()
        @param: return_t(record_t::*)(signature_t...)
        @return: 'Function' object.
        * accepts a non-const-member-function pointer with any arguments.
        * called on object returned by 'RecordBuilder<record_t>::method()'
        * template params are auto deduced from the pointer passed.
    */  template<class record_t, class return_t, class ...signature_t>
        const Function build(return_t(record_t::* pFunctor)(signature_t...)) const
        {
            return buildMethodFunctor(pFunctor);
        }
    };
}