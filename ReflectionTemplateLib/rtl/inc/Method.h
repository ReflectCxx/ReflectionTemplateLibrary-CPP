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
        Return invokeCtor(alloc pAllocType, const detail::FunctorId& pClonerId, _args&&...params) const;

    public:

        Method() = default;
        Method(Method&&) = default;
        Method(const Method&) = default;
        Method& operator=(Method&&) = default;
        Method& operator=(const Method&) = default;

        using Function::bind;

        template<class ..._args>
        constexpr const detail::ErasedCaller<_args...> operator()(_args&&...params) const noexcept = delete;

        GETTER_BOOL(Const, (getQualifier() == detail::methodQ::Const));

        template<class _recordType, class ..._signature>
        constexpr detail::Hopper<_recordType> to() const;

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

        template<class ..._signature>
        friend struct detail::DefaultInvoker;

        template<class ..._signature>
        friend struct detail::NonConstInvoker;

        template<class _recordType>
        friend struct detail::ErasedInvoker;
    };
}