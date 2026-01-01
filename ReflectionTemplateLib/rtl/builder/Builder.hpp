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

#include "Builder.h"
#include "ReflectionBuilder.hpp"

namespace rtl::builder
{    
    inline CtorBuilder::CtorBuilder(const std::string& pNamespace, const std::string& pRecordStr,
                                    const std::string& pFunction, traits::uid_t pRecordUid)
        : ReflectionBuilder(pFunction, pRecordUid, pRecordStr, pNamespace) {
    }

/*  @method: build()
    @param: none
    @return: 'Function' object.
    * accepts no arguments, builds copy constructor which takes const object source.
    * called on object returned by 'RecordBuilder<_recordType>::constructor<...>()'
    * template params <...>, explicitly specified.
    * calling with zero template params will build the default constructor ie, 'RecordBuilder<_recordType>::constructor()'
*/  template<class _recordType, class ..._signature>
    inline const Function CtorBuilder::build() const
    {
        return buildConstructor<_recordType, _signature...>();
    }   
}


namespace rtl::builder
{
    inline Builder<detail::member::None>::Builder(traits::uid_t pRecordUid, const std::string& pFunction, const std::string& pNamespace)
        : ReflectionBuilder(pFunction, pRecordUid, detail::RECORD_NONE, pNamespace) {
    }

/*  @method: build()
    @param: _returnType(*)(_signature...)
    @return: 'Function' object.
    * accepts all non-member and static-member function pointer.
    * called on the objects returned by 'type::function()' & 'RecordBuilder<_recordType>::methodStatic(..)'.
    * template params are auto deduced from the function pointer passed.
*/	template<class _returnType, class ..._signature>
    inline const Function Builder<detail::member::None>::build(_returnType(*pFunctor)(_signature...)) const
    {
        return buildFunctor(pFunctor, detail::member::None);
    }
}


namespace rtl::builder
{
    inline Builder<detail::member::None, void>::Builder(traits::uid_t pRecordUid, const std::string& pFunction, const std::string& pNamespace)
        : ReflectionBuilder(pFunction, pRecordUid, detail::RECORD_NONE, pNamespace)
    { }

/*  @method: build()
    @param: _returnType(*)()
    @return: 'Function' object.
    * accepts a non-member or static-member function pointer with no arguments.
    * called on objects returned by 'type::function<void>(..)' & 'RecordBuilder<_recordType>::methodStatic<void>(..)'
    * template param 'void' is explicitly specified.
*/  template<class _returnType>
    inline const Function Builder<detail::member::None, void>::build(_returnType(*pFunctor)()) const
    {
        return buildFunctor(pFunctor, detail::member::None);
    }
}


namespace rtl::builder
{
    template<class ..._signature>
    inline Builder<detail::member::None, _signature...>::Builder(traits::uid_t pRecordUid, const std::string& pFunction, const std::string& pNamespace)
        : ReflectionBuilder(pFunction, pRecordUid, detail::RECORD_NONE, pNamespace)
    { }


/*  @method: build()
    @param: _returnType(*)(_signature...)
    @return: 'Function' object.
    * it accepts a non-member or static-member function pointer.
    * called on objects returned by 'type::function<...>(..)' & 'RecordBuilder<_recordType>::methodStatic<...>(..)'.
    * template params are explicitly specified.
*/  template<class ..._signature>
    template<class _returnType>
    inline const Function Builder<detail::member::None, _signature...>::build(_returnType(*pFunctor)(_signature...)) const
    {
        return buildFunctor(pFunctor, detail::member::None);
    }
}


namespace rtl::builder
{
    inline Builder<detail::member::Static>::Builder(traits::uid_t pRecordUid, const std::string& pFunction,
                                                    const std::string& pRecordStr, const std::string& pNamespace)
        : ReflectionBuilder(pFunction, pRecordUid, pRecordStr, pNamespace)
    { }

/*  @method: build()
    @param: _returnType(*)(_signature...)
    @return: 'Function' object.
    * accepts all non-member and static-member function pointer.
    * called on the objects returned by 'type::function()' & 'RecordBuilder<_recordType>::methodStatic(..)'.
    * template params are auto deduced from the function pointer passed.
*/	template<class _returnType, class ..._signature>
    inline const Function Builder<detail::member::Static>::build(_returnType(*pFunctor)(_signature...)) const
    {
        return buildFunctor(pFunctor, detail::member::Static);
    }
}


namespace rtl::builder
{
    inline Builder<detail::member::Static, void>::Builder(traits::uid_t pRecordUid, const std::string& pFunction,
                                                          const std::string& pRecordStr, const std::string& pNamespace)
        : ReflectionBuilder(pFunction, pRecordUid, pRecordStr, pNamespace)
    { }

/*  @method: build()
    @param: _returnType(*)()
    @return: 'Function' object.
    * accepts a non-member or static-member function pointer with no arguments.
    * called on objects returned by 'type::function<void>(..)' & 'RecordBuilder<_recordType>::methodStatic<void>(..)'
    * template param 'void' is explicitly specified.
*/  template<class _returnType>
    inline const Function Builder<detail::member::Static, void>::build(_returnType(*pFunctor)()) const
    {
        return buildFunctor(pFunctor, detail::member::Static);
    }
}


namespace rtl::builder
{
    template<class ..._signature>
    inline Builder<detail::member::Static, _signature...>::Builder(traits::uid_t pRecordUid, const std::string& pFunction,
                                                                   const std::string& pRecordStr, const std::string& pNamespace)
        : ReflectionBuilder(pFunction, pRecordUid, pRecordStr, pNamespace)
    { }


/*  @method: build()
    @param: _returnType(*)(_signature...)
    @return: 'Function' object.
    * it accepts a non-member or static-member function pointer.
    * called on objects returned by 'type::function<...>(..)' & 'RecordBuilder<_recordType>::methodStatic<...>(..)'.
    * template params are explicitly specified.
*/  template<class ..._signature>
    template<class _returnType>
    inline const Function Builder<detail::member::Static, _signature...>::build(_returnType(*pFunctor)(_signature...)) const
    {
        return buildFunctor(pFunctor, detail::member::Static);
    }
}


namespace rtl::builder
{
    inline Builder<detail::member::Const>::Builder(const std::string& pFunction, traits::uid_t pRecordUid)
        : ReflectionBuilder(pFunction, pRecordUid, detail::INIT_LATER, detail::INIT_LATER)
    { }

/*  @method: build()
    @param: _returnType(_recordType::*)(_signature...) const.
    @return: 'Function' object.
    * accepts function pointer of a const-member-function with any signature. 
    * called on object returned by 'RecordBuilder<_recordType>::methodConst()'
    * template params will be auto deduced from the function pointer passed.
*/  template<class _recordType, class _returnType, class ..._signature>
    inline const Function Builder<detail::member::Const>::build(_returnType(_recordType::* pFunctor)(_signature...) const) const
    {
        return buildMethodFunctor(pFunctor);
    }
}


namespace rtl::builder
{
    inline Builder<detail::member::Const, void>::Builder(const std::string& pFunction, traits::uid_t pRecordUid)
        : ReflectionBuilder(pFunction, pRecordUid, detail::INIT_LATER, detail::INIT_LATER)
    { }

/*  @method: build()
    @param: _returnType(_recordType::*)() const.
    @return: 'Function' object.
    * accepts a const-member-function pointer with no arguments.
    * called on object returned by 'RecordBuilder<_recordType>::methodConst<void>()'
    * template param 'void' is explicitly specified.
*/  template<class _recordType, class _returnType>
    inline const Function Builder<detail::member::Const, void>::build(_returnType(_recordType::* pFunctor)() const) const
    {
        return buildMethodFunctor(pFunctor);
    }
}


namespace rtl::builder 
{
    template<class ..._signature>
    inline Builder<detail::member::Const, _signature...>::Builder(const std::string& pFunction, traits::uid_t pRecordUid)
        : ReflectionBuilder(pFunction, pRecordUid, detail::INIT_LATER, detail::INIT_LATER)
    { }

/*  @method: build()
    @param: _returnType(_recordType::*)(_signature...) const.
    @return: 'Function' object.
    * accepts a const-member-function pointer with any arguments.
    * called on object returned by 'RecordBuilder<_recordType>::methodConst<...>()'
    * template param are explicitly specified.
*/  template<class ..._signature>
    template<class _recordType, class _returnType>
    inline const Function Builder<detail::member::Const, _signature...>::build(_returnType(_recordType::* pFunctor)(_signature...) const) const
    {
        return buildMethodFunctor(pFunctor);
    }
}


namespace rtl::builder
{
    inline Builder<detail::member::NonConst>::Builder(const std::string& pFunction, traits::uid_t pRecordUid)
        : ReflectionBuilder(pFunction, pRecordUid, detail::INIT_LATER, detail::INIT_LATER)
    { }


/*  @method: build()
    @param: _returnType(_recordType::*)(_signature...)
    @return: 'Function' object.
    * accepts a non-const-member-function pointer with any arguments.
    * called on object returned by 'RecordBuilder<_recordType>::method()'
    * template params are auto deduced from the pointer passed.
*/  template<class _recordType, class _returnType, class ..._signature>
    inline const Function Builder<detail::member::NonConst>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
    {
        return buildMethodFunctor(pFunctor);
    }
}


namespace rtl::builder
{
    inline Builder<detail::member::NonConst, void>::Builder(const std::string& pFunction, traits::uid_t pRecordUid)
        : ReflectionBuilder(pFunction, pRecordUid, detail::INIT_LATER, detail::INIT_LATER)
    { }


/*  @method: build()
    @param: _returnType(_recordType::*)()
    @return: 'Function' object.
    * accepts a non-const-member-function pointer with no arguments.
    * called on object returned by 'RecordBuilder<_recordType>::method<void>()'
    * template param 'void' is explicitly specified.
*/  template<class _recordType, class _returnType>
    inline const Function Builder<detail::member::NonConst, void>::build(_returnType(_recordType::* pFunctor)()) const
    {
        return buildMethodFunctor(pFunctor);
    }
}


namespace rtl::builder
{
    template<class ..._signature>
    inline Builder<detail::member::NonConst, _signature...>::Builder(const std::string& pFunction, traits::uid_t pRecordUid)
        : ReflectionBuilder(pFunction, pRecordUid, detail::INIT_LATER, detail::INIT_LATER)
    { }
    
/*  @method: build()
    @param: _returnType(_recordType::*)(_signature...)
    @return: 'Function' object.
    * accepts a non-const-member-function pointer with any arguments.
    * called on object returned by 'RecordBuilder<_recordType>::method<...>()'
    * template params are explicitly specified.
*/  template<class ..._signature>
    template<class _recordType, class _returnType>
    inline const Function Builder<detail::member::NonConst, _signature...>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
    {
        return buildMethodFunctor(pFunctor);
    }
}