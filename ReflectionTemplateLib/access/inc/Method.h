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

#include "RObject.h"
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
        Method(const Function& pFunction, const detail::FunctorId& pFunctorId, const std::string& pFunctorName)
            : Function(pFunction, pFunctorId, pFunctorName)
        { }

        //invokes the constructor associated with this 'Method'
        template<class ..._args>
        Return invokeCtor(alloc pAllocType, std::size_t pClonerIndex, _args&&...params) const;

    public:

        Method() = default;
        Method(Method&&) = default;
        Method(const Method&) = default;
        Method& operator=(Method&&) = default;
        Method& operator=(const Method&) = default;

        using Function::bind;

        GETTER_BOOL(Const, (getQualifier() == detail::methodQ::Const));

        //indicates if a particular set of arguments accepted by the functor associated with it.
        template<class ..._args>
        bool hasSignature() const;

        template<class ..._signature>
        const detail::DefaultInvoker<_signature...> bind(const RObject& pTarget) const;

        template<class ..._signature>
        const detail::NonConstInvoker<_signature...> bind(constCast<RObject>&& pTarget) const;

    /*  @method: operator()()
        @return: lambda
        * accepts no arguments for 'target', since associated functor is static-member-functions.
        * returns a lambda, which forwards the call to finally call the associated static-member-function functor.
        * provides syntax like,'method()(params...)', first'()' is empty & second'()' takes the actual params.
    */  constexpr auto operator()() const
        {
            return detail::FunctionCaller<>{ this };
        }


    /*  @method: operator()(const RObject&)
        @param: const RObject& (target object)
        @return: lambda
        * accepts 'pTarget', which contains the actual object on which the member-function functor associated with 'this' is invoked.
        * returns a lambda, which forwards the call to 'call', finally invoking the associated non-static-member-function functor.
        * provides syntax like, 'method(pTarget)(params...)', keeping the target & params seperate.
    */  constexpr detail::DefaultInvoker<> operator()(const RObject& pTarget) const
        {
            return detail::DefaultInvoker<>{ this, &pTarget };
        }

        constexpr detail::NonConstInvoker<> operator()(constCast<RObject>&& pTarget) const
        {
            return detail::NonConstInvoker<>{ this, &pTarget.m_target };
        }

        //friends :)
        friend Record;
        friend detail::CxxReflection;

        template<class ..._signature>
        friend struct detail::DefaultInvoker;

        template<class ..._signature>
        friend struct detail::NonConstInvoker;
    };
}