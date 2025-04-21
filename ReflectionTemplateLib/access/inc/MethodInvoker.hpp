#pragma once

#include "Method.h"
#include "Instance.h"
#include "MethodInvoker.h"

namespace rtl 
{
    namespace access
    {
        template<class ..._signature>
        //MethodInvoker, holds only 'Method' associated with a static-member-function.
        inline MethodInvoker<FunctorType::Static, _signature...>::MethodInvoker(const Method& pMethod)
            :m_method(pMethod) {
        }

        template<class ..._signature>
        template<class ..._args>
        inline RStatus MethodInvoker<FunctorType::Static, _signature...>::call(_args&& ...params) const noexcept
        {
            //invokes the static-member-function functor associated with 'm_method'. no need of 'm_target' as other 'MethodInvoker'.
            return m_method.invokeStatic<_args...>(std::forward<_args>(params)...);
        }
    }


    namespace access
    {
        //MethodInvoker, holds const-ref of the 'Method' and 'Instance' on which it will be invoked.
        template<FunctorType _type, class ..._signature>
        inline MethodInvoker<_type, _signature...>::MethodInvoker(const Method& pMethod, const Instance& pTarget)
            : m_method(pMethod)
            , m_target(pTarget) {
        }


    /*  @method: call()
        @params: params... (corresponding to functor associated with 'm_method')
        @return: RStatus, indicating success of the reflected call.
        * invokes non-static-member-function functor associated with 'm_method' on object 'm_target'.
    */  template<FunctorType _type, class ..._signature>
        template<class ..._args>
        inline RStatus MethodInvoker<_type, _signature...>::call(_args&& ...params) const noexcept
        {
            if (m_target.isEmpty()) {
                //if the target is empty.
                return RStatus(Error::EmptyInstance);
            }

            if (m_target.getTypeId() != m_method.getRecordTypeId()) {
                //if the m_target's type-id & type-id of the 'class/struct' owner of the associated functor(m_method's) do not match.
                return RStatus(Error::InstanceTypeMismatch);
            }

            if constexpr (sizeof...(_signature) == 0) 
            {
                using containerMute = detail::MethodContainer<TypeQ::Mute, std::remove_reference_t<_args>...>;
                using containerConst = detail::MethodContainer<TypeQ::Const, std::remove_reference_t<_args>...>;
                switch (m_target.getQualifier()) {
                    //if the target is non-const, const & non-const both type member-function can be invoked on it.
                case TypeQ::Mute: return m_method.invoke<containerMute, containerConst, _args...>(m_target, std::forward<_args>(params)...);
                    //if the m_target is const, only const member function can be invoked on it.
                case TypeQ::Const: return m_method.invokeConst<containerMute, containerConst, _args...>(m_target, std::forward<_args>(params)...);
                }
            }
            else
            {
                using containerMute = detail::MethodContainer<TypeQ::Mute, _signature...>;
                using containerConst = detail::MethodContainer<TypeQ::Const, _signature...>;
                switch (m_target.getQualifier()) {
                    //if the target is non-const, const & non-const both type member-function can be invoked on it.
                case TypeQ::Mute: return m_method.invoke<containerMute, containerConst, _args...>(m_target, std::forward<_args>(params)...);
                    //if the m_target is const, only const member function can be invoked on it.
                case TypeQ::Const: return m_method.invokeConst<containerMute, containerConst, _args...>(m_target, std::forward<_args>(params)...);
                }
            }
            //only an empty 'Instance' will have TypeQ::None.
            return RStatus(Error::EmptyInstance);
        }
    }
}