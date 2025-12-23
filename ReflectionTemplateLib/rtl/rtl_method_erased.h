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

#include "functor.h"
#include "RObject.hpp"

namespace rtl
{
    template<class ...signature_t>
    struct method<RObject, Return(signature_t...)>
    {
        struct invoker
        {
            const RObject& target;
            const method<RObject, Return(signature_t...)>& fn;

            template<class ...args_t> requires (sizeof...(args_t) == sizeof...(signature_t))
            [[nodiscard]] [[gnu::hot]] [[gnu::flatten]]
            constexpr Return operator()(args_t&&...params) const noexcept
            {
                if (fn.m_last_err != error::None) [[unlikely]] {
                    return { fn.m_last_err, RObject{} };
                }

                auto index = (fn.m_functors[detail::call_by::value] != nullptr ? detail::call_by::value : detail::call_by::cref);
                if (fn.m_functors[index]->is_void())
                {
                    fn.m_vhop[index] (*(fn.m_functors[index]), target, std::forward<args_t>(params)...);
                    return { error::None, RObject{} };
                }
                else
                {
                    return { error::None,
                             RObject{ fn.m_rhop[index] (*(fn.m_functors[index]), target, std::forward<args_t>(params)...),
                                      fn.m_functors[index]->get_robject_id()
                             }
                    };
                }
            }
        };

        template<class ...fwd_args_t>
        struct perfect_fwd
        {
            const RObject& target;
            const method<RObject, Return(signature_t...)>& fn;

            template<class ...args_t>
            [[nodiscard]] [[gnu::hot]] [[gnu::flatten]]
            constexpr Return operator()(args_t&&...params) const noexcept
            {
                if (fn.m_last_err != error::None) [[unlikely]] {
                    return { fn.m_last_err, RObject{} };
                }

                auto signature_id = traits::uid<traits::strict_sign_id_t<fwd_args_t...>>::value;
                for (int index = 0; index < fn.m_functors.size(); index++)
                {
                    if (fn.m_functors[index] != nullptr)
                    {
                        if (signature_id == fn.m_functors[index]->get_strict_sign_id())
                        {
                            if (fn.m_functors[index]->is_void())
                            {
                                fn.m_vhop[index] (*fn.m_functors[index], target, std::forward<args_t>(params)...);
                                return { error::None, RObject{} };
                            }
                            else
                            {
                                return { error::None,
                                         RObject{ fn.m_rhop[index] (*fn.m_functors[index], target, std::forward<args_t>(params)...),
                                                  fn.m_functors[index]->get_robject_id()
                                         }
                                };
                            }
                        }
                    }
                }
                return { error::RefBindingMismatch, RObject{} };
            }
        };

        constexpr invoker operator()(RObject& p_target) const noexcept {
            validate(p_target);
            return invoker{ p_target, *this };
        }

        constexpr invoker operator()(RObject&& p_target) const noexcept {
            validate(p_target);
            return invoker{ p_target, *this };
        }

        template<class ...args_t>
        requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind(RObject& p_target) const noexcept {
            validate(p_target);
            return perfect_fwd<args_t...>{ p_target, *this };
        }

        template<class ...args_t>
        requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind(RObject&& p_target) const noexcept {
            validate(p_target);
            return perfect_fwd<args_t...>{ p_target, *this };
        }

        constexpr operator bool() const noexcept {
            return !(m_last_err != error::None || m_functors.empty() ||
                     (m_functors.size() == 1 && m_functors[0] == nullptr));
        }

        constexpr bool must_bind_refs() const noexcept {
            return (m_functors[detail::call_by::value] == nullptr && m_functors.size() > detail::call_by::ncref);
        }

        GETTER(rtl::error, _init_error, m_last_err)

    private:

        using lambda_vt = std::function<void(const dispatch::functor&, const RObject&, signature_t...)>;

        using lambda_rt = std::function<std::any(const dispatch::functor&, const RObject&, signature_t...)>;

        std::vector<lambda_rt> m_rhop = {};

        std::vector<lambda_vt> m_vhop = {};

        std::vector<const dispatch::functor*> m_functors = {};
        
        mutable traits::uid_t m_record_id = traits::uid<>::none;

        mutable error m_last_err = error::InvalidCaller;

        GETTER_REF(std::vector<lambda_rt>, _rhop, m_rhop)
        GETTER_REF(std::vector<lambda_vt>, _vhop, m_vhop)
        GETTER_REF(std::vector<const dispatch::functor*>, _overloads, m_functors)
            
        constexpr void set_record_id(const traits::uid_t p_recid) const {
            m_record_id = p_recid;
        }
        
        constexpr void set_init_error(const error p_err) const {
            m_last_err = p_err;
        }

        constexpr void validate(const RObject& p_target) const
        {
            if (m_last_err == error::None) [[unlikely]]
            {
                if (p_target.isEmpty()) {
                    m_last_err = error::EmptyRObject;
                    return;
                }
                if (m_record_id != p_target.getTypeId()) {
                    m_last_err = error::TargetTypeMismatch;
                    return;
                }
                if (must_bind_refs()) {
                    m_last_err = error::ExplicitRefBindingRequired;
                    return;
                }
            }
        }

        template<class, class ...>
        friend struct detail::HopMethod;

        static_assert((!std::is_reference_v<signature_t> && ...),
                      "rtl::method<...>: any type cannot be specified as reference here.");
    };
}