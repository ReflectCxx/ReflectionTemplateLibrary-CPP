#pragma once
#include "Method.h"

namespace rtl 
{
    namespace access 
	{
        //MethodInvoker, holds const-ref of the 'Method' and 'Instance' on which it will be invoked.
        template<FunctorType _type>
        inline MethodInvoker<_type>::MethodInvoker(const Method& pMethod, const Instance& pTarget) 
            : m_method(pMethod)
            , m_target(pTarget) {
        }


    /*  @method: call()
        @params: params... (corresponding to functor associated with 'm_method')
        @return: RStatus, indicating success of the reflected call.
        * invokes non-static-member-function functor associated with 'm_method' on object 'm_target'.
	*/  template<FunctorType _type>
        template<class ..._args>
        inline RStatus MethodInvoker<_type>::call(_args ...params) const noexcept
        {
            if (m_target.isEmpty()) {
                //if the target is empty.
                return RStatus(Error::EmptyInstance);
            }

            if (m_target.getTypeId() != m_method.getRecordTypeId()) {
			//if the m_target's type-id & type-id of the 'class/struct' owner of the associated functor(m_method's) do not match.
                return RStatus(Error::InstanceTypeMismatch);
            }

            switch (m_target.getQualifier())
            {
                //if the target is non-const, const & non-const both type member-function can be invoked on it.
                case TypeQ::Mute: return m_method.invoke(m_target, params...);

                //if the m_target is const, only const member function can be invoked on it.
                case TypeQ::Const: return m_method.invokeConst(m_target, params...);
            }

			//only an empty 'Instance' will have TypeQ::None.
            return RStatus(Error::EmptyInstance);
        }

        //MethodInvoker, holds only 'Method' associated with a static-member-function.
        inline MethodInvoker<FunctorType::Static>::MethodInvoker(const Method& pMethod)
            :m_method(pMethod) {
        }


        template<class ..._args>
        inline RStatus MethodInvoker<FunctorType::Static>::call(_args ...params) const noexcept
        {
            //invokes the static-member-function functor associated with 'm_method'. no need of 'm_target' as other 'MethodInvoker'.
            return m_method.invokeStatic(params...);
        }
    }


    namespace access
	{
    /*  @method: on()
        @return: MethodInvoker<FunctorType::Static>
        * accepts no arguments for 'target', since associated functor is static-member-functions.
    */  inline const MethodInvoker<FunctorType::Static> Method::on() const
        {
            return MethodInvoker<FunctorType::Static>(*this);
        }


        inline const MethodInvoker<FunctorType::Method> Method::on(const Instance& pTarget) const
        {
            return MethodInvoker<FunctorType::Method>(*this, pTarget);
        }


    /*  @method: invokeCtor()
        @params: variable arguments.
        @return: RStatus
        * calls the constructor with given arguments.
    */  template<class ..._args>
        inline RStatus Method::invokeCtor(_args ...params) const
        {
            return Function::operator()(params...);
        }


    /*  @method: invokeStatic()
	    @params: variable arguments.
	    @return: RStatus
	    * with given arguments, calls the static-member-function functor associated with this 'Method'.
    */  template<class ..._args>
        inline RStatus Method::invokeStatic(_args ...params) const
        {
            return Function::operator()(params...);
        }


    /*  @method: hasSignature<void>()
        @return: bool
        * checks if the member-function functor associated with this 'Method', takes zero arguments or not.
    */  template<>
        inline const bool Method::hasSignature<void>() const
        {
            switch (getQualifier())
            {
                case TypeQ::None: return Function::hasSignature<void>();
                case TypeQ::Mute: return (hasSignatureId(detail::MethodContainer<TypeQ::Mute>::getContainerId()) != -1);
                case TypeQ::Const: return (hasSignatureId(detail::MethodContainer<TypeQ::Const>::getContainerId()) != -1);
            }
            return false;
        }


    /*  @method: hasSignature<...>()
        @params: template params, <_arg0, ..._args> (expects at least one args- _args0)
        @return: bool
        * checks if the member-function functor associated with this 'Method', takes template specified arguments set or not.
    */  template<class _arg0, class ..._args>
        inline const bool Method::hasSignature() const
        {
            switch (getQualifier())
            {
                case TypeQ::None: return Function::hasSignature<_arg0, _args...>();
                case TypeQ::Mute: return (hasSignatureId(detail::MethodContainer<TypeQ::Mute, _arg0, _args...>::getContainerId()) != -1);
                case TypeQ::Const: return (hasSignatureId(detail::MethodContainer<TypeQ::Const, _arg0, _args...>::getContainerId()) != -1);
            }
            return false;
        }


    /*  @method: invokeConst()
        @params: 'pTarget' (on which the method to be invoked), 'params...' (method arguments)
        @return: 'RStatus', indicating the success of reflected method call.
        * invokes only a const-member-function functor.
    */  template<class ..._args>
        inline RStatus Method::invokeConst(const Instance& pTarget, _args ...params) const
        {
            //if the given argument's associated MethodContainer contains such member-functor, then make the call.
            const std::size_t& index = hasSignatureId(detail::MethodContainer<TypeQ::Const, _args...>::getContainerId());
            if (index != -1)
            {
                //make the call.
                return detail::MethodContainer<TypeQ::Const, _args...>::forwardCall(pTarget.get(), index, params...);
            }
            else {
                //if the associated MethodContainer contains no such member-functor, check if such functor is present in container holding non-const functors.
                const std::size_t& index = hasSignatureId(detail::MethodContainer<TypeQ::Mute, _args...>::getContainerId());
                if (index != -1) {
                    //if yes, then return error indicating such 'functor' is present but can be called on only non-const 'Instance'.
                    return RStatus(Error::InstanceConstMismatch);
                }
            }
            //return this error if the given argument's associated MethodContainer not found (const/non-const both).
            return RStatus(Error::SignatureMismatch);
        }


    /*  @method: invokeConst()
        @params: 'pTarget' (on which the method to be invoked), 'params...' (method arguments)
        @return: 'RStatus', indicating the success of reflected method call.
        * can invoke a 'const' or non-const-member-function functor.
    */  template<class ..._args>
        inline RStatus Method::invoke(const Instance& pTarget, _args ...params) const
        {
            //if the given argument's associated MethodContainer contains such member-functor, then make the call.
            const std::size_t& index = hasSignatureId(detail::MethodContainer<TypeQ::Mute, _args...>::getContainerId());
            if (index != -1)
            {
                //make the call.
                return detail::MethodContainer<TypeQ::Mute, _args...>::forwardCall(pTarget.get(), index, params...);
            }
            else {
                //if no such member-functor is found in non-const MethodContainer, check if such functor is present in const MethodContainer.
                return invokeConst(pTarget, params...);
            }
        }
    }
}