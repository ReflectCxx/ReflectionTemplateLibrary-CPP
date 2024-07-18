#pragma once

#include "Builder.h"

namespace rtl {

    namespace builder
    {
        inline Builder<TypeQ::None>::Builder(const std::string& pNamespace, const std::string& pRecord,
                                             const std::string& pFunction)
            : ReflectionBuilder(pNamespace, pRecord, pFunction) {
        }

    /* this build() will accept all non-member and static-member function pointer, even the ones with zero args (only
       in absence of any other overloaded function)
    */	template<class _returnType, class ..._signature>
        inline constexpr const access::Function Builder<TypeQ::None>::build(_returnType(*pFunctor)(_signature...)) const
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

    /* This build() only accepts a function pointer with no arguments. If there is an overloaded function with
       zero arguments, the compiler will not be able to auto deduce which function pointer to pick.
       In those cases <void> must be expicitly specified (ie, function<void>().build()) to make the compiler to
       pick the function pointer taking zero arguments.
    */  template<class _returnType>
        inline constexpr const access::Function Builder<TypeQ::None, void>::build(_returnType(*pFunctor)()) const
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

    /*  this build() accepts function pointer with signature that is explicitly specified by 'function<..>()' template params. */
        template<class ..._signature>
        template<class _returnType>
        inline constexpr const access::Function Builder<TypeQ::None, _signature...>::build(_returnType(*pFunctor)(_signature...)) const
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


        template<class _recordType, class _returnType, class ..._signature>
        inline constexpr const access::Function Builder<TypeQ::Const>::build(_returnType(_recordType::* pFunctor)(_signature...) const) const
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

    /* This build() only accepts a const-member-function pointer with no arguments. If there is an overloaded
       const-member-function with zero arguments, the compiler will not be able to auto deduce which function pointer to pick.
       In those cases <void> must be expicitly specified (ie, methodConst<void>().build()) to make the compiler to
       pick the const-member-function pointer taking zero arguments.
    */  template<class _recordType, class _returnType>
        inline constexpr const access::Function Builder<TypeQ::Const, void>::build(_returnType(_recordType::* pFunctor)() const) const
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

        template<class ..._signature>
        template<class _recordType, class _returnType>
        inline constexpr const access::Function Builder<TypeQ::Const, _signature...>::build(_returnType(_recordType::* pFunctor)(_signature...) const) const
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


        template<class _recordType, class ..._signature>
        inline constexpr const access::Function
        Builder<TypeQ::Mute>::build(enable_if_same<_recordType&, typename detail::TypeId<_signature...>::HEAD > *_) const
        {
            return buildCopyConstructor<_recordType, _signature...>();
        }


        template<class _recordType, class ..._signature>
        inline constexpr const access::Function
        Builder<TypeQ::Mute>::build(enable_if_same<const _recordType&, typename detail::TypeId<_signature...>::HEAD > *_) const
        {
            return buildConstCopyConstructor<_recordType, _signature...>();
        }


        template<class _recordType, class ..._signature>
        inline constexpr const access::Function
        Builder<TypeQ::Mute>::build(enable_if_not_same<_recordType&, typename detail::TypeId<_signature...>::HEAD > *_,
                                    enable_if_not_same<const _recordType&, typename detail::TypeId<_signature...>::HEAD > *__) const
        {
            return buildConstructor<_recordType, _signature...>();
        }


        template<class _recordType, class _returnType, class ..._signature>
        inline constexpr const access::Function Builder<TypeQ::Mute>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
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

        template<class _recordType, class _returnType>
        inline constexpr const access::Function Builder<TypeQ::Mute, void>::build(_returnType(_recordType::* pFunctor)()) const
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
		
        template<class ..._signature>
        template<class _recordType, class _returnType>
        inline constexpr const access::Function Builder<TypeQ::Mute, _signature...>::build(_returnType(_recordType::* pFunctor)(_signature...)) const
        {
            return buildMethodFunctor(pFunctor);
        }
    }
}