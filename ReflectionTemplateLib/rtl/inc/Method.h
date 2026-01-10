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

#include <functional>

#include "Function.h"
#include "MethodInvoker.h"

namespace rtl {

    class Record;

/*  @class: Method
    * extends 'Function' class and adds interfaces to call member function.
    * invokes only static & non-static member functions via reflection.
    * deletes the base's 'operator()()'.
    * redefines 'operator()()', to accept only target object and returns lambda.
    * the returned lambda is then called with the arguments corresponding to the functor associated with it.
*/  class Method : public Function
    {
        //private ctor, called by 'Record' class.
        Method(const Function& pFunction)
            : Function(pFunction)
        { }

        //private ctor, called by 'Record' class.
        Method(const Function& pFunction, const type_meta& pFunctorMeta, const detail::FunctorId& pFunctorId, const std::string& pFunctorName)
            : Function(pFunction, pFunctorMeta, pFunctorId, pFunctorName)
        { }

    public:

        Method() = default;
        Method(Method&&) = default;
        Method(const Method&) = default;
        Method& operator=(Method&&) = default;
        Method& operator=(const Method&) = default;

        template<class ...signatureT>
        constexpr const detail::InitFunctionHop<detail::member::Static, signatureT...> argsT() const;

        template<class recordT = RObject, class ...signatureT> requires (!std::is_const_v<recordT>)
        constexpr detail::HopBuilder<detail::member::NonConst, recordT> targetT() const;

        template<class recordT = RObject, class ...signatureT> requires (std::is_const_v<recordT>)
        constexpr detail::HopBuilder<detail::member::Const, std::remove_const_t<recordT>> targetT() const;

        //indicates if a particular set of arguments accepted by the functor associated with it.
        template<class ..._args>
        bool hasSignature() const;

        template<class ..._signature>
        const detail::DefaultInvoker<_signature...> bind(const RObject& pTarget) const;

        template<class ..._signature>
        const detail::NonConstInvoker<_signature...> bind(constCast<RObject>&& pTarget) const;

        template<class _recordType>
        constexpr const detail::ErasedInvoker<_recordType> operator()(_recordType&& pTarget) const
        {
            return detail::ErasedInvoker<_recordType>{ (*this), pTarget };
        }

        friend Record;
        friend detail::CxxReflection;

        template<class...>
        friend struct detail::DefaultInvoker;

        template<class...>
        friend struct detail::NonConstInvoker;

        template<class>
        friend struct detail::ErasedInvoker;
    };
}