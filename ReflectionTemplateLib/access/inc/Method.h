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
    private:

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
        std::pair<error, RObject> invokeCtor(alloc&& pAllocType, _args&&...params) const;

    public:

        using Function::bind;

        //indicates if a particular set of arguments accepted by the functor associated with it.
        template<class ..._args>
        bool hasSignature() const;

        template<class ..._signature>
        const detail::DefaultInvoker<_signature...> bind(const RObject& pTarget) const;

        template<class ..._signature>
        const detail::NonConstInvoker<_signature...> bind(constCast<RObject>&& pTarget) const;

        //friends :)
        friend Record;
        friend detail::CxxReflection;

        template<class ..._signature>
        friend class detail::DefaultInvoker;

        template<class ..._signature>
        friend class detail::NonConstInvoker;

    public:

        GETTER_BOOL(Const, (getQualifier() == detail::methodQ::Const));

    /*  @method: operator()()
        @return: lambda
        * accepts no arguments for 'target', since associated functor is static-member-functions.
        * returns a lambda, which forwards the call to finally call the associated static-member-function functor.
        * provides syntax like,'method()(params...)', first'()' is empty & second'()' takes the actual params.
    */  constexpr auto operator()() const
        {
            return [this](auto&&...params) {
                return Function::operator()(std::forward<decltype(params)> (params)...);
            };
        }


    /*  @method: operator()(const RObject&)
        @param: const RObject& (target object)
        @return: lambda
        * accepts 'pTarget', which contains the actual object on which the member-function functor associated with 'this' is invoked.
        * returns a lambda, which forwards the call to 'call', finally invoking the associated non-static-member-function functor.
        * provides syntax like, 'method(pTarget)(params...)', keeping the target & params seperate.
    */  constexpr auto operator()(const RObject& pTarget) const
        {
            return [&](auto&&...params)-> std::pair<error, RObject> {
                return bind(pTarget).call(std::forward<decltype(params)>(params)...);
            };
        }
    };
}