#pragma once

#include "Method.h"
#include "Instance.h"
#include "MethodInvoker.h"

namespace rtl 
{
    namespace access
    {
        //MethodInvoker, holds const-ref of the 'Method' and 'Instance' on which it will be invoked.
        template<class ..._signature>
        inline MethodInvoker<_signature...>::MethodInvoker(const Method& pMethod, const Instance& pTarget)
            : m_method(pMethod)
            , m_target(pTarget) {
        }


    /*  @method: call()
        @params: params... (corresponding to functor associated with 'm_method')
        @return: RStatus, indicating success of the reflected call.
        * invokes non-static-member-function functor associated with 'm_method' on object 'm_target'.
    */  template<class ..._signature>
        template<class ..._args>
        inline RStatus MethodInvoker<_signature...>::call(_args&& ...params) const noexcept
        {
            if (m_target.isEmpty()) {
                //if the target is empty.
                return RStatus(Error::EmptyInstance);
            }
            if (m_target.getTypeId() != m_method.getRecordTypeId()) {
                //if the m_target's type-id & type-id of the 'class/struct' owner of the associated functor(m_method's) do not match.
                return RStatus(Error::InstanceTypeMismatch);
            }
            if constexpr (sizeof...(_signature) == 0) {
                return Invoker<std::remove_reference_t<_args>...>::invoke(m_method, m_target, std::forward<_args>(params)...);
            }
            else {
                return Invoker<_signature...>::invoke(m_method, m_target, std::forward<_args>(params)...);
            }
        }


        // Invoker struct's static method definition
        template<class ..._signature>
        template<class ..._finalSignature>
        template<class ..._args>
        inline RStatus MethodInvoker<_signature...>::Invoker<_finalSignature...>::invoke(const Method& pMethod,
                                                                                         const Instance& pTarget,
                                                                                         _args&&... params)
        {
            using containerMute = detail::MethodContainer<TypeQ::Mute, _finalSignature...>;
            using containerConst = detail::MethodContainer<TypeQ::Const, _finalSignature...>;

            switch (pTarget.getQualifier())
            {
            case TypeQ::Mute: {

                //if the target is non-const, then const & non-const both type of member-function can be invoked on it.
                const std::size_t& index = pMethod.hasSignatureId(containerMute::getContainerId());
                if (index != -1) {
                    return containerMute::template forwardCall<_args...>(pTarget.get(), index, std::forward<_args>(params)...);
                }
                const std::size_t& indexConst = pMethod.hasSignatureId(containerConst::getContainerId());
                if (indexConst != -1) {
                    return containerConst::template forwardCall<_args...>(pTarget.get(), indexConst, std::forward<_args>(params)...);
                }
                break;
            }
            case TypeQ::Const: {

                //if the pTarget is const, only const member function can be invoked on it.
                const std::size_t& indexConst = pMethod.hasSignatureId(containerConst::getContainerId());
                if (indexConst != -1) {
                    return containerConst::template forwardCall<_args...>(pTarget.get(), indexConst, std::forward<_args>(params)...);
                }
                const std::size_t& index = pMethod.hasSignatureId(containerMute::getContainerId());
                if (index != -1) {
                    //if Const-MethodContainer contains no such member-functor and functor is present in Non-Const-MethodContainer.
                    return RStatus(Error::InstanceConstMismatch);
                }
                break;
            }
            //only an empty 'Instance' will have TypeQ::None.
            case TypeQ::None: return RStatus(Error::EmptyInstance);
            }
            return RStatus(Error::SignatureMismatch);
        }
    }
}