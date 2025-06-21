#pragma once

#include "RStatus.h"
#include "Function.h"
#include "Instance.h"
#include "FunctionCaller.hpp"

namespace rtl {

    namespace access
    {
        template<class ..._signature>
        inline const FunctionCaller<_signature...> Function::bind() const
        {
            return FunctionCaller<_signature...>(*this);
        }

    /*  @method: hasSignature<...>()
        @param: set of arguments, explicitly specified as template parameter.
        @return: bool, if the functor associated with this object is of certain signature or not.
        * a single 'Function' object can be associated with multiple overloads of same function.
        * the set of arguments passed is checked agains all registered overloads, returns true if matched with any one.
    */  template<class ..._args>
        inline const bool Function::hasSignature() const
        {
            //hasSignatureId() returns the index of the 'lambda' in functor-container, which cannot be '-1'.
            return (hasSignatureId(detail::FunctorContainer<_args...>::getContainerId()) != -1);
        }


    /*  @method: operator()()
        @param: variadic arguments.
        @return: RStatus, containing the call status & return value of from the reflected call.
        * if the arguments did not match with any overload, returns RStatus with error::SignatureMismatch
        * providing optional syntax, Function::call() does the exact same thing.
    */  template<class ..._args>
        inline RStatus Function::operator()(_args&& ...params) const noexcept
        {
            return bind().call(std::forward<_args>(params)...);
        }
    }
}
