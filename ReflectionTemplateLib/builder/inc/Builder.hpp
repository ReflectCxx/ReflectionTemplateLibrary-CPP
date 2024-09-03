#pragma once

#include "Builder.h"

namespace rtl {

    namespace builder
    {
        inline Builder<TypeQ::None>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                             const std::string& pFunction)
            : ReflectionBuilder(pNamespace, pRecord, pFunction) {
        }

    /*  @method: build()
        @param: _returnType(*)(_signature...)
        @return: 'access::Function' object.
        * accepts all non-member and static-member function pointer.
        * called on the objects returned by 'Reflect::function()' & 'RecordBuilder<_recordType>::methodStatic(..)'.
        * template params are auto deduced from the function pointer passed.
    */	template<class _returnType, class ..._signature>
        inline const access::Function Builder<TypeQ::None>::build(_returnType(*pFunctor)(_signature...)) const
        {
            return buildFunctor(pFunctor);
        }
    }


    namespace builder
	{
        inline Builder<TypeQ::None, void>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                                   const std::string& pFunction)
            : ReflectionBuilder(pNamespace, pRecord, pFunction) {
        }

    /*  @method: build()
        @param: _returnType(*)()
        @return: 'access::Function' object.
        * accepts a non-member or static-member function pointer with no arguments.
        * called on objects returned by 'Reflect::function<void>(..)' & 'RecordBuilder<_recordType>::methodStatic<void>(..)'
        * template param 'void' is explicitly specified.
    */  template<class _returnType>
        inline const access::Function Builder<TypeQ::None, void>::build(_returnType(*pFunctor)()) const
        {
            return buildFunctor(pFunctor);
        }
    }


    namespace builder
    {
        template<class ..._signature>
        inline Builder<TypeQ::None, _signature...>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                                            const std::string& pFunction)
            : ReflectionBuilder(pNamespace, pRecord, pFunction) {
        }


    /*  @method: build()
        @param: _returnType(*)(_signature...)
        @return: 'access::Function' object.
        * it accepts a non-member or static-member function pointer.
        * called on objects returned by 'Reflect::function<...>(..)' & 'RecordBuilder<_recordType>::methodStatic<...>(..)'.
        * template params are explicitly specified.
    */  template<class ..._signature>
        template<class _returnType>
        inline const access::Function Builder<TypeQ::None, _signature...>::build(_returnType(*pFunctor)(_signature...)) const
        {
            return buildFunctor(pFunctor);
        }
    }


    namespace builder
    {
        inline Builder<TypeQ::Const>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                              const std::string& pFunction)
            : ReflectionBuilder(pNamespace, pRecord, pFunction) {
        }

    /*  @method: build()
        @param: _returnType(_recordType::*)(_signature...) const.
        @return: 'access::Function' object.
        * accepts function pointer of a const-member-function with any signature. 
        * called on object returned by 'RecordBuilder<_recordType>::methodConst()'
        * template params will be auto deduced from the function pointer passed.
    */  template<class _recordType, class _returnType, class ..._signature>
        inline const access::Function Builder<TypeQ::Const>::build(_returnType(_recordType::* pFunctor)(_signature...) const) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }


    namespace builder
    {
        inline Builder<TypeQ::Const, void>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                                    const std::string& pFunction)
            : ReflectionBuilder(pNamespace, pRecord, pFunction) {
        }

    /*  @method: build()
        @param: _returnType(_recordType::*)() const.
        @return: 'access::Function' object.
        * accepts a const-member-function pointer with no arguments.
        * called on object returned by 'RecordBuilder<_recordType>::methodConst<void>()'
        * template param 'void' is explicitly specified.
    */  template<class _recordType, class _returnType>
        inline const access::Function Builder<TypeQ::Const, void>::build(_returnType(_recordType::* pFunctor)() const) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }
	

    namespace builder 
    {
        template<class ..._signature>
        inline Builder<TypeQ::Const, _signature...>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                                             const std::string& pFunction)
            : ReflectionBuilder(pNamespace, pRecord, pFunction) {
        }

    /*  @method: build()
        @param: _returnType(_recordType::*)(_signature...) const.
        @return: 'access::Function' object.
        * accepts a const-member-function pointer with any arguments.
        * called on object returned by 'RecordBuilder<_recordType>::methodConst<...>()'
        * template param are explicitly specified.
    */  template<class ..._signature>
        template<class _recordType, class _returnType>
        inline const access::Function Builder<TypeQ::Const, _signature...>::build(_returnType(_recordType::* pFunctor)(_signature...) const) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }


    namespace builder
    {
        inline Builder<TypeQ::Mute>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                             const std::string& pFunction)
            : ReflectionBuilder(pNamespace, pRecord, pFunction) {
        }


    /*  @method: build()
        @param: none
        @return: 'access::Function' object.
        * accepts no arguments, builds copy constructor which takes const object source.
        * called on object returned by 'RecordBuilder<_recordType>::constructor<...>()'
        * template params <...>, explicitly specified.
        * calling with zero template params will build the default constructor ie, 'RecordBuilder<_recordType>::constructor()'
    */  template<class _recordType, class ..._signature>
        inline const access::Function Builder<TypeQ::Mute>::build() const
        {
            //this code-block is retained by compiler, if copy constructor with non-const ref('_recordType&') is being registered.
            if constexpr (std::is_same_v<_recordType&, typename detail::TypeId<_signature...>::HEAD>)
            {
                return buildCopyConstructor<_recordType, _signature...>();
            }
            //this code-block is retained by compiler, if copy constructor with const-ref('const _recordType&') is being registered.
            else if constexpr (std::is_same_v<const _recordType&, typename detail::TypeId<_signature...>::HEAD>)
            {
                return buildConstCopyConstructor<_recordType, _signature...>();
            }
            //if any other constructor except, copy constructor is being registered, this code-block will be retained.
            else 
            {
                return buildConstructor<_recordType, _signature...>();
            }
        }


    /*  @method: build()
        @param: _returnType(_recordType::*)(_signature...)
        @return: 'access::Function' object.
        * accepts a non-const-member-function pointer with any arguments.
        * called on object returned by 'RecordBuilder<_recordType>::method()'
        * template params are auto deduced from the pointer passed.
    */  template<class _recordType, class _returnType, class ..._signature>
        inline const access::Function Builder<TypeQ::Mute>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }

  
    namespace builder
    {
        inline Builder<TypeQ::Mute, void>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                                   const std::string& pFunction)
            : ReflectionBuilder(pNamespace, pRecord, pFunction) {
        }


    /*  @method: build()
        @param: _returnType(_recordType::*)()
        @return: 'access::Function' object.
        * accepts a non-const-member-function pointer with no arguments.
        * called on object returned by 'RecordBuilder<_recordType>::method<void>()'
        * template param 'void' is explicitly specified.
    */  template<class _recordType, class _returnType>
        inline const access::Function Builder<TypeQ::Mute, void>::build(_returnType(_recordType::* pFunctor)()) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }


    namespace builder
    {
        template<class ..._signature>
        inline Builder<TypeQ::Mute, _signature...>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                                            const std::string& pFunction)
            : ReflectionBuilder(pNamespace, pRecord, pFunction) {
        }
		
    /*  @method: build()
        @param: _returnType(_recordType::*)(_signature...)
        @return: 'access::Function' object.
        * accepts a non-const-member-function pointer with any arguments.
        * called on object returned by 'RecordBuilder<_recordType>::method<...>()'
        * template params are explicitly specified.
    */  template<class ..._signature>
        template<class _recordType, class _returnType>
        inline const access::Function Builder<TypeQ::Mute, _signature...>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }
}
