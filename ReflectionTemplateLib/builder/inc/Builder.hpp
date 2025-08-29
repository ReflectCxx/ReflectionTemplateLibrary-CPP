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

#include "TypeId.h"
#include "Builder.h"
#include "ReflectionBuilder.hpp"

namespace rtl
{
    namespace builder
    {
        inline CtorBuilder::CtorBuilder(const std::string_view pNamespace, const std::string_view pRecord,
                                        const std::string_view pFunction, std::size_t pRecordId)
            : ReflectionBuilder(pFunction, pRecordId, pNamespace, pRecord) {
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
}


namespace rtl
{
    namespace builder
    {
        inline Builder<detail::methodQ::None>::Builder(std::size_t pRecordId, const std::string_view pFunction, const std::string_view pNamespace)
            : ReflectionBuilder(pFunction, pRecordId, pNamespace) {
        }

    /*  @method: build()
        @param: _returnType(*)(_signature...)
        @return: 'Function' object.
        * accepts all non-member and static-member function pointer.
        * called on the objects returned by 'Reflect::function()' & 'RecordBuilder<_recordType>::methodStatic(..)'.
        * template params are auto deduced from the function pointer passed.
    */	template<class _returnType, class ..._signature>
        inline const Function Builder<detail::methodQ::None>::build(_returnType(*pFunctor)(_signature...)) const
        {
            return buildFunctor(pFunctor);
        }
    }


    namespace builder
    {
        inline Builder<detail::methodQ::None, void>::Builder(std::size_t pRecordId, const std::string_view pFunction, const std::string_view pNamespace)
            : ReflectionBuilder(pFunction, pRecordId, pNamespace)
        { }

    /*  @method: build()
        @param: _returnType(*)()
        @return: 'Function' object.
        * accepts a non-member or static-member function pointer with no arguments.
        * called on objects returned by 'Reflect::function<void>(..)' & 'RecordBuilder<_recordType>::methodStatic<void>(..)'
        * template param 'void' is explicitly specified.
    */  template<class _returnType>
        inline const Function Builder<detail::methodQ::None, void>::build(_returnType(*pFunctor)()) const
        {
            return buildFunctor(pFunctor);
        }
    }


    namespace builder
    {
        template<class ..._signature>
        inline Builder<detail::methodQ::None, _signature...>::Builder(std::size_t pRecordId, const std::string_view pFunction, const std::string_view pNamespace)
            : ReflectionBuilder(pFunction, pRecordId, pNamespace)
        { }


    /*  @method: build()
        @param: _returnType(*)(_signature...)
        @return: 'Function' object.
        * it accepts a non-member or static-member function pointer.
        * called on objects returned by 'Reflect::function<...>(..)' & 'RecordBuilder<_recordType>::methodStatic<...>(..)'.
        * template params are explicitly specified.
    */  template<class ..._signature>
        template<class _returnType>
        inline const Function Builder<detail::methodQ::None, _signature...>::build(_returnType(*pFunctor)(_signature...)) const
        {
            return buildFunctor(pFunctor);
        }
    }


    namespace builder
    {
        inline Builder<detail::methodQ::Const>::Builder(const std::string_view pFunction, std::size_t pRecordId)
            : ReflectionBuilder(pFunction, pRecordId)
        { }

    /*  @method: build()
        @param: _returnType(_recordType::*)(_signature...) const.
        @return: 'Function' object.
        * accepts function pointer of a const-member-function with any signature. 
        * called on object returned by 'RecordBuilder<_recordType>::methodConst()'
        * template params will be auto deduced from the function pointer passed.
    */  template<class _recordType, class _returnType, class ..._signature>
        inline const Function Builder<detail::methodQ::Const>::build(_returnType(_recordType::* pFunctor)(_signature...) const) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }


    namespace builder
    {
        inline Builder<detail::methodQ::Const, void>::Builder(const std::string_view pFunction, std::size_t pRecordId)
            : ReflectionBuilder(pFunction, pRecordId)
        { }

    /*  @method: build()
        @param: _returnType(_recordType::*)() const.
        @return: 'Function' object.
        * accepts a const-member-function pointer with no arguments.
        * called on object returned by 'RecordBuilder<_recordType>::methodConst<void>()'
        * template param 'void' is explicitly specified.
    */  template<class _recordType, class _returnType>
        inline const Function Builder<detail::methodQ::Const, void>::build(_returnType(_recordType::* pFunctor)() const) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }
	

    namespace builder 
    {
        template<class ..._signature>
        inline Builder<detail::methodQ::Const, _signature...>::Builder(const std::string_view pFunction, std::size_t pRecordId)
            : ReflectionBuilder(pFunction, pRecordId)
        { }

    /*  @method: build()
        @param: _returnType(_recordType::*)(_signature...) const.
        @return: 'Function' object.
        * accepts a const-member-function pointer with any arguments.
        * called on object returned by 'RecordBuilder<_recordType>::methodConst<...>()'
        * template param are explicitly specified.
    */  template<class ..._signature>
        template<class _recordType, class _returnType>
        inline const Function Builder<detail::methodQ::Const, _signature...>::build(_returnType(_recordType::* pFunctor)(_signature...) const) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }


    namespace builder
    {
        inline Builder<detail::methodQ::NonConst>::Builder(const std::string_view pFunction, std::size_t pRecordId)
            : ReflectionBuilder(pFunction, pRecordId)
        { }


    /*  @method: build()
        @param: _returnType(_recordType::*)(_signature...)
        @return: 'Function' object.
        * accepts a non-const-member-function pointer with any arguments.
        * called on object returned by 'RecordBuilder<_recordType>::method()'
        * template params are auto deduced from the pointer passed.
    */  template<class _recordType, class _returnType, class ..._signature>
        inline const Function Builder<detail::methodQ::NonConst>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }

  
    namespace builder
    {
        inline Builder<detail::methodQ::NonConst, void>::Builder(const std::string_view pFunction, std::size_t pRecordId)
            : ReflectionBuilder(pFunction, pRecordId)
        { }


    /*  @method: build()
        @param: _returnType(_recordType::*)()
        @return: 'Function' object.
        * accepts a non-const-member-function pointer with no arguments.
        * called on object returned by 'RecordBuilder<_recordType>::method<void>()'
        * template param 'void' is explicitly specified.
    */  template<class _recordType, class _returnType>
        inline const Function Builder<detail::methodQ::NonConst, void>::build(_returnType(_recordType::* pFunctor)()) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }


    namespace builder
    {
        template<class ..._signature>
        inline Builder<detail::methodQ::NonConst, _signature...>::Builder(const std::string_view pFunction, std::size_t pRecordId)
            : ReflectionBuilder(pFunction, pRecordId)
        { }
		
    /*  @method: build()
        @param: _returnType(_recordType::*)(_signature...)
        @return: 'Function' object.
        * accepts a non-const-member-function pointer with any arguments.
        * called on object returned by 'RecordBuilder<_recordType>::method<...>()'
        * template params are explicitly specified.
    */  template<class ..._signature>
        template<class _recordType, class _returnType>
        inline const Function Builder<detail::methodQ::NonConst, _signature...>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }
}