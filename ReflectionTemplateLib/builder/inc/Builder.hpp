/*****************************************************************
 *                                                               *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP  *
 *  Copyright (c) 2025 Neeraj Singh (reflectcxx@outlook.com)     *
 *  SPDX-License-Identifier: MIT                                 *
 *                                                               *
 *****************************************************************/


#pragma once

#include "TypeId.h"
#include "Builder.h"
#include "ReflectionBuilder.hpp"

namespace rtl {

    namespace builder
    {
        inline Builder<methodQ::None>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                             const std::string& pFunction, std::size_t pRecordId)
            : ReflectionBuilder(pNamespace, pRecord, pFunction, pRecordId) {
        }

    /*  @method: build()
        @param: _returnType(*)(_signature...)
        @return: 'access::Function' object.
        * accepts all non-member and static-member function pointer.
        * called on the objects returned by 'Reflect::function()' & 'RecordBuilder<_recordType>::methodStatic(..)'.
        * template params are auto deduced from the function pointer passed.
    */	template<class _returnType, class ..._signature>
        inline const access::Function Builder<methodQ::None>::build(_returnType(*pFunctor)(_signature...)) const
        {
            return buildFunctor(pFunctor);
        }
    }


    namespace builder
    {
        inline Builder<methodQ::None, void>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                                   const std::string& pFunction, std::size_t pRecordId)
            : ReflectionBuilder(pNamespace, pRecord, pFunction, pRecordId) {
        }

    /*  @method: build()
        @param: _returnType(*)()
        @return: 'access::Function' object.
        * accepts a non-member or static-member function pointer with no arguments.
        * called on objects returned by 'Reflect::function<void>(..)' & 'RecordBuilder<_recordType>::methodStatic<void>(..)'
        * template param 'void' is explicitly specified.
    */  template<class _returnType>
        inline const access::Function Builder<methodQ::None, void>::build(_returnType(*pFunctor)()) const
        {
            return buildFunctor(pFunctor);
        }
    }


    namespace builder
    {
        template<class ..._signature>
        inline Builder<methodQ::None, _signature...>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                                            const std::string& pFunction, std::size_t pRecordId)
            : ReflectionBuilder(pNamespace, pRecord, pFunction, pRecordId) {
        }


    /*  @method: build()
        @param: _returnType(*)(_signature...)
        @return: 'access::Function' object.
        * it accepts a non-member or static-member function pointer.
        * called on objects returned by 'Reflect::function<...>(..)' & 'RecordBuilder<_recordType>::methodStatic<...>(..)'.
        * template params are explicitly specified.
    */  template<class ..._signature>
        template<class _returnType>
        inline const access::Function Builder<methodQ::None, _signature...>::build(_returnType(*pFunctor)(_signature...)) const
        {
            return buildFunctor(pFunctor);
        }
    }


    namespace builder
    {
        inline Builder<methodQ::Const>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                              const std::string& pFunction, std::size_t pRecordId)
            : ReflectionBuilder(pNamespace, pRecord, pFunction, pRecordId) {
        }

    /*  @method: build()
        @param: _returnType(_recordType::*)(_signature...) const.
        @return: 'access::Function' object.
        * accepts function pointer of a const-member-function with any signature. 
        * called on object returned by 'RecordBuilder<_recordType>::methodConst()'
        * template params will be auto deduced from the function pointer passed.
    */  template<class _recordType, class _returnType, class ..._signature>
        inline const access::Function Builder<methodQ::Const>::build(_returnType(_recordType::* pFunctor)(_signature...) const) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }


    namespace builder
    {
        inline Builder<methodQ::Const, void>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                                    const std::string& pFunction, std::size_t pRecordId)
            : ReflectionBuilder(pNamespace, pRecord, pFunction, pRecordId) {
        }

    /*  @method: build()
        @param: _returnType(_recordType::*)() const.
        @return: 'access::Function' object.
        * accepts a const-member-function pointer with no arguments.
        * called on object returned by 'RecordBuilder<_recordType>::methodConst<void>()'
        * template param 'void' is explicitly specified.
    */  template<class _recordType, class _returnType>
        inline const access::Function Builder<methodQ::Const, void>::build(_returnType(_recordType::* pFunctor)() const) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }
	

    namespace builder 
    {
        template<class ..._signature>
        inline Builder<methodQ::Const, _signature...>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                                             const std::string& pFunction, std::size_t pRecordId)
            : ReflectionBuilder(pNamespace, pRecord, pFunction, pRecordId) {
        }

    /*  @method: build()
        @param: _returnType(_recordType::*)(_signature...) const.
        @return: 'access::Function' object.
        * accepts a const-member-function pointer with any arguments.
        * called on object returned by 'RecordBuilder<_recordType>::methodConst<...>()'
        * template param are explicitly specified.
    */  template<class ..._signature>
        template<class _recordType, class _returnType>
        inline const access::Function Builder<methodQ::Const, _signature...>::build(_returnType(_recordType::* pFunctor)(_signature...) const) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }


    namespace builder
    {
        inline Builder<methodQ::NonConst>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                             const std::string& pFunction, std::size_t pRecordId)
            : ReflectionBuilder(pNamespace, pRecord, pFunction, pRecordId) {
        }


    /*  @method: build()
        @param: none
        @return: 'access::Function' object.
        * accepts no arguments, builds copy constructor which takes const object source.
        * called on object returned by 'RecordBuilder<_recordType>::constructor<...>()'
        * template params <...>, explicitly specified.
        * calling with zero template params will build the default constructor ie, 'RecordBuilder<_recordType>::constructor()'
    */  template<class _recordType, class ..._signature>
        inline const access::Function Builder<methodQ::NonConst>::build() const
        {
            constexpr bool isCopyCtorSignature = (sizeof...(_signature) == 1 && traits::is_first_type_same_v<_recordType, _signature...>);
            static_assert(!isCopyCtorSignature, "Copy-constructor registration detected! It is implicitly registered with other constructors.");
            return buildConstructor<_recordType, _signature...>();
        }


    /*  @method: build()
        @param: _returnType(_recordType::*)(_signature...)
        @return: 'access::Function' object.
        * accepts a non-const-member-function pointer with any arguments.
        * called on object returned by 'RecordBuilder<_recordType>::method()'
        * template params are auto deduced from the pointer passed.
    */  template<class _recordType, class _returnType, class ..._signature>
        inline const access::Function Builder<methodQ::NonConst>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }

  
    namespace builder
    {
        inline Builder<methodQ::NonConst, void>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                                   const std::string& pFunction, std::size_t pRecordId)
            : ReflectionBuilder(pNamespace, pRecord, pFunction, pRecordId) {
        }


    /*  @method: build()
        @param: _returnType(_recordType::*)()
        @return: 'access::Function' object.
        * accepts a non-const-member-function pointer with no arguments.
        * called on object returned by 'RecordBuilder<_recordType>::method<void>()'
        * template param 'void' is explicitly specified.
    */  template<class _recordType, class _returnType>
        inline const access::Function Builder<methodQ::NonConst, void>::build(_returnType(_recordType::* pFunctor)()) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }


    namespace builder
    {
        template<class ..._signature>
        inline Builder<methodQ::NonConst, _signature...>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                                            const std::string& pFunction, std::size_t pRecordId)
            : ReflectionBuilder(pNamespace, pRecord, pFunction, pRecordId) {
        }
		
    /*  @method: build()
        @param: _returnType(_recordType::*)(_signature...)
        @return: 'access::Function' object.
        * accepts a non-const-member-function pointer with any arguments.
        * called on object returned by 'RecordBuilder<_recordType>::method<...>()'
        * template params are explicitly specified.
    */  template<class ..._signature>
        template<class _recordType, class _returnType>
        inline const access::Function Builder<methodQ::NonConst, _signature...>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }
}