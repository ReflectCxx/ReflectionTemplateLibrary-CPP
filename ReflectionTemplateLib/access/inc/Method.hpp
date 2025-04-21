#pragma once
#include "Method.h"
#include "MethodInvoker.hpp"

namespace rtl
{
    namespace access
    {

    /*  @method: on()
        @return: MethodInvoker<FunctorType::Static>
        * accepts no arguments for 'target', since associated functor is static-member-functions.
    */  inline const MethodInvoker<FunctorType::Static> Method::bind() const
        {
            return MethodInvoker<FunctorType::Static>(*this);
        }


    /*  @method: on()
        @return: MethodInvoker<FunctorType::Method>
        * accepts 'pTarget', which contains the actual object on which the member-function functor associated with 'this' is invoked.
    */  inline const MethodInvoker<FunctorType::Method> Method::bind(const Instance& pTarget) const
        {
            return MethodInvoker<FunctorType::Method>(*this, pTarget);
        }

        template<class ..._signature>
        inline const MethodInvoker<FunctorType::Static, _signature...> Method::bind() const
        {
            return MethodInvoker<FunctorType::Static, _signature...>(*this);
        }

        template<class ..._signature>
        inline const MethodInvoker<FunctorType::Method, _signature...> Method::bind(const Instance& pTarget) const
        {
            return MethodInvoker<FunctorType::Method, _signature...>(*this, pTarget);
        }


    /*  @method: invokeCtor()
        @params: variable arguments.
        @return: RStatus
        * calls the constructor with given arguments.
    */  template<class ..._args>
        inline RStatus Method::invokeCtor(_args&& ...params) const
        {
            return Function::operator()<_args...>(std::forward<_args>(params)...);
        }


    /*  @method: invokeStatic()
        @params: variable arguments.
        @return: RStatus
        * with given arguments, calls the static-member-function functor associated with this 'Method'.
    */  template<class ..._args>
        inline RStatus Method::invokeStatic(_args&& ...params) const
        {
            return Function::operator()<_args...>(std::forward<_args>(params)...);
        }


    /*  @method: hasSignature<...>()
        @params: template params, <_arg0, ..._args> (expects at least one args- _args0)
        @return: bool
        * checks if the member-function functor associated with this 'Method', takes template specified arguments set or not.
    */  template<class ..._args>
        inline const bool Method::hasSignature() const
        {
            switch (getQualifier())
            {
                case TypeQ::None: {
                    return Function::hasSignature<_args...>();
                }
                case TypeQ::Mute: {
                    using Container = detail::MethodContainer<TypeQ::Mute, _args...>;
                    return (hasSignatureId(Container::getContainerId()) != -1);
                }
                case TypeQ::Const: {
                    using Container = detail::MethodContainer<TypeQ::Const, _args...>;
                    return (hasSignatureId(Container::getContainerId()) != -1);
                }
            }
            return false;
        }


    /*  @method: invokeConst()
        @params: 'pTarget' (on which the method to be invoked), 'params...' (method arguments)
        @return: 'RStatus', indicating the success of reflected method call.
        * can invoke a 'const' or non-const-member-function functor.
    */  template<class _containerMute, class _containerConst, class ..._args>
        inline RStatus Method::invoke(const Instance& pTarget, _args&& ...params) const
        {
            //if the given argument's associated MethodContainer contains such member-functor, then make the call.
            const std::size_t& index = hasSignatureId(_containerMute::getContainerId());
            if (index != -1) {
                //make the call.
                return _containerMute::template forwardCall<_args...>(pTarget.get(), index, std::forward<_args>(params)...);
            }
            else {
                //if no such member-functor is found in non-const MethodContainer, check if such functor is present in const MethodContainer and call.
                return invokeConst<_containerMute, _containerConst, _args...>(pTarget, std::forward<_args>(params)...);
            }
        }


    /*  @method: invokeConst()
        @params: 'pTarget' (on which the method to be invoked), 'params...' (method arguments)
        @return: 'RStatus', indicating the success of reflected method call.
        * invokes only a const-member-function functor.
    */  template<class _containerMute, class _containerConst, class ..._args>
        inline RStatus Method::invokeConst(const Instance& pTarget, _args&& ...params) const
        {
            //if the given argument's associated MethodContainer contains such member-functor, then make the call.
            const std::size_t& index = hasSignatureId(_containerConst::getContainerId());
            if (index != -1) {
                //make the call.
                return _containerConst::template forwardCall<_args...>(pTarget.get(), index, std::forward<_args>(params)...);
            }
            else {
                //if the associated MethodContainer contains no such member-functor, check if such functor is present in container holding non-const functors.
                const std::size_t& index = hasSignatureId(_containerMute::getContainerId());
                if (index != -1) {
                    //if yes, then return error indicating such 'functor' is present but can be called on only non-const 'Instance'.
                    return RStatus(Error::InstanceConstMismatch);
                }
            }
            //return this error if the given argument's associated MethodContainer not found (const/non-const both).
            return RStatus(Error::SignatureMismatch);
        }
    }
}