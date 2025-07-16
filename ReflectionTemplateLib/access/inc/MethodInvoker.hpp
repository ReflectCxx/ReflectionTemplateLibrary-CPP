#pragma once

#include "Method.h"
#include "RObject.h"
#include "MethodInvoker.h"
#include "MethodContainer.h"

namespace rtl 
{
    namespace access
    {
        //MethodInvoker, holds const-ref of the 'Method' and 'RObject' on which it will be invoked.
        template<class ..._signature>
        inline MethodInvoker<_signature...>::MethodInvoker(const Method& pMethod, const RObject& pTarget)
            : m_method(pMethod)
            , m_target(pTarget) {
        }


    /*  @method: call()
        @params: params... (corresponding to functor associated with 'm_method')
        @return: RObject, indicating success of the reflected call.
        * invokes non-static-member-function functor associated with 'm_method' on object 'm_target'.
    */  template<class ..._signature>
        template<class ..._args>
        inline std::pair<error, RObject> MethodInvoker<_signature...>::call(_args&& ...params) const noexcept
        {
            if (m_target.isEmpty()) {
                //if the target is empty.
                return { error::EmptyRObject, RObject() };
            }
            if (m_target.getTypeId() != m_method.getRecordTypeId()) {
                //if the m_target's type-id & type-id of the 'class/struct' owner of the associated functor(m_method's) do not match.
                return { error::ReflectedObjectTypeMismatch, RObject() };
            }
            if constexpr (sizeof...(_signature) == 0) {
                error err;
                return { err, Invoker<remove_const_n_reference<_args>...>::invoke(err, m_method, m_target, std::forward<_args>(params)...) };
            }
            else {
                error err;
                return { err, Invoker<_signature...>::invoke(err, m_method, m_target, std::forward<_args>(params)...) };
            }
        }


        // Invoker struct's static method definition
        template<class ..._signature>
        template<class ..._finalSignature>
        template<class ..._args>
        inline RObject MethodInvoker<_signature...>::Invoker<_finalSignature...>::invoke(error& pError,
                                                                                         const Method& pMethod,
                                                                                         const RObject& pTarget,
                                                                                         _args&&... params)
        {
            using containerMute = detail::MethodContainer<methodQ::NonConst, _finalSignature...>;
            using containerConst = detail::MethodContainer<methodQ::Const, _finalSignature...>;

            switch (pTarget.getQualifier())
            {
            case methodQ::NonConst: {

                //if the target is non-const, then const & non-const both type of member-function can be invoked on it.
                std::size_t index = pMethod.hasSignatureId(containerMute::getContainerId());
                if (index != rtl::index_none) {
                    return containerMute::template forwardCall<_args...>(pError, pTarget, index, std::forward<_args>(params)...);
                }
                std::size_t indexConst = pMethod.hasSignatureId(containerConst::getContainerId());
                if (indexConst != rtl::index_none) {
                    return containerConst::template forwardCall<_args...>(pError, pTarget, indexConst, std::forward<_args>(params)...);
                }
                break;
            }
            case methodQ::Const: {

                //if the pTarget is const, only const member function can be invoked on it.
                std::size_t indexConst = pMethod.hasSignatureId(containerConst::getContainerId());
                if (indexConst != rtl::index_none) {
                    return containerConst::template forwardCall<_args...>(pError, pTarget, indexConst, std::forward<_args>(params)...);
                    
                }
                std::size_t index = pMethod.hasSignatureId(containerMute::getContainerId());
                if (index != rtl::index_none) {
                    //if Const-MethodContainer contains no such member-functor and functor is present in Non-Const-MethodContainer.
                    pError = error::ReflecetdObjectConstMismatch;
                    return RObject();
                }
                break;
            }
            //only an empty 'RObject' will have methodQ::None.
            case methodQ::None: {
                pError = error::EmptyRObject;
                return RObject();
            }
            }
            pError = error::SignatureMismatch;
            return RObject();
        }
    }
}