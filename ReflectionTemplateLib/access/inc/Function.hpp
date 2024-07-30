#pragma once

#include "RStatus.h"
#include "Function.h"
#include "Instance.h"
#include "FunctorContainer.h"

namespace rtl {

    namespace access
    {
    /*  @method: hasSignature<...>()
        @param: set of arguments, explicitly specified as template parameter. 
        @return: bool, if the functor associated with this object is of certain signature or not.
        * a single 'Function' object can be associated with multiple overloads of same function.
        * the set of arguments passed is checked agains all registered overloads, returns true if matched with any one.
    */  template<class _arg0, class ..._args>
		inline const bool Function::hasSignature() const
		{
			//hasSignatureId() returns the index of the 'lambda' in functor-container, which cannot be '-1'.
			return (hasSignatureId(detail::FunctorContainer<_arg0, _args...>::getContainerId()) != -1);
		}


    /*  @method: hasSignature<void>()
        @param: set of arguments, explicitly specified as template parameter. 
        @return: bool, if the functor associated with this object doesn't takes any argument.
    */  template<>
		inline const bool Function::hasSignature<void>() const
		{
			//hasSignatureId() returns the index of 'lambda' in functor-container, which cannot be '-1'.
			return (hasSignatureId(detail::FunctorContainer<>::getContainerId()) != -1);
		}


    /*  @method: operator()()
        @param: variadic arguments.
        @return: RStatus, containing the call status & return value of from the reflected call.
        * if the arguments did not match with any overload, returns RStatus with Error::SignatureMismatch
		* providing optional syntax, Function::call() does the exact same thing.
    */  template<class ..._args>
		inline RStatus Function::operator()(_args ...params) const noexcept
		{
			const std::size_t& index = hasSignatureId(detail::FunctorContainer<_args...>::getContainerId());
			if (index != -1) //true, if the arguments sent matches the functor signature associated with this 'Function' object
			{
				return detail::FunctorContainer<_args...>::forwardCall(index, params...);
			}
			//else return with Error::SignatureMismatch.
			return RStatus(Error::SignatureMismatch);
		}


    /*  @method: call()
        @param: variadic arguments.
        @return: RStatus, containing the call status & return value of from the reflected call.
        * if the arguments did not match with any overload, returns RStatus with Error::SignatureMismatch.
        * providing optional syntax, Function::operator()() does the exact same thing.
    */  template<class ..._args>
		inline RStatus Function::call(_args ...params) const noexcept
		{
			const std::size_t& index = hasSignatureId(detail::FunctorContainer<_args...>::getContainerId());
			if (index != -1) //true, if the arguments sent matches the functor signature associated with this 'Function' object
			{
				return detail::FunctorContainer<_args...>::forwardCall(index, params...);
			}
			//else return with Error::SignatureMismatch.
			return RStatus(Error::SignatureMismatch);
		}
	}
}