#pragma once

#include "Method.h"
#include "Instance.h"
#include "MethodInvoker.h"

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
        inline RStatus MethodInvoker<_type>::call(_args&& ...params) const noexcept
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
            case TypeQ::Mute: return m_method.invoke<_args...>(m_target, std::forward<_args>(params)...);

                //if the m_target is const, only const member function can be invoked on it.
            case TypeQ::Const: return m_method.invokeConst<_args...>(m_target, std::forward<_args>(params)...);
            }

            //only an empty 'Instance' will have TypeQ::None.
            return RStatus(Error::EmptyInstance);
        }
    }


    namespace access
    {
        //MethodInvoker, holds only 'Method' associated with a static-member-function.
        inline MethodInvoker<FunctorType::Static>::MethodInvoker(const Method& pMethod)
            :m_method(pMethod) {
        }

        template<class ..._args>
        inline RStatus MethodInvoker<FunctorType::Static>::call(_args&& ...params) const noexcept
        {
            //invokes the static-member-function functor associated with 'm_method'. no need of 'm_target' as other 'MethodInvoker'.
            return m_method.invokeStatic<_args...>(std::forward<_args>(params)...);
        }

    /*  @method: on()
        @return: MethodInvoker<FunctorType::Static>
        * accepts no arguments for 'target', since associated functor is static-member-functions.
    */  inline const MethodInvoker<FunctorType::Static> Method::on() const
        {
            return MethodInvoker<FunctorType::Static>(*this);
        }


    /*  @method: on()
        @return: MethodInvoker<FunctorType::Method>
        * accepts 'pTarget', which contains the actual object on which the member-function functor associated with 'this' is invoked.
    */  inline const MethodInvoker<FunctorType::Method> Method::on(const Instance& pTarget) const
        {
            return MethodInvoker<FunctorType::Method>(*this, pTarget);
        }
	}
}