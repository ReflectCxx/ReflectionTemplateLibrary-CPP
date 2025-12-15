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
                if (!fn) [[unlikely]] {
                    return { fn.m_init_err, RObject{} };
                }

                if (target.isEmpty()) {
                    return { error::EmptyRObject, RObject{} };
                }

                if (fn.must_bind_refs()) [[unlikely]] {
                    return { error::ExplicitRefBindingRequired, RObject{} };
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
                                      fn.m_functors[index]->get_robject_id(), nullptr
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
                if (!fn) [[unlikely]] {
                    return { fn.m_init_err, RObject{} };
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
                                                  fn.m_functors[index]->get_robject_id(), nullptr
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
            return invoker{ p_target, *this };
        }

        constexpr invoker operator()(RObject&& p_target) const noexcept {
            return invoker{ p_target, *this };
        }

        template<class ...args_t>
        requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind(RObject& p_target) const noexcept {
            return perfect_fwd<args_t...>{ p_target, *this };
        }

        template<class ...args_t>
        requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind(RObject&& p_target) const noexcept {
            return perfect_fwd<args_t...>{ p_target, *this };
        }

        constexpr operator bool() const noexcept {
            return !(m_init_err != error::None || m_functors.empty() ||
                     (m_functors.size() == 1 && m_functors[0] == nullptr));
        }

        constexpr bool must_bind_refs() const noexcept {
            return (m_functors[detail::call_by::value] == nullptr &&
                   (m_functors.size() > detail::call_by::ncref || m_functors[detail::call_by::cref]->is_any_arg_ncref()));
        }

        GETTER(rtl::error, _init_error, m_init_err)

    private:

        using lambda_vt = std::function<void(const dispatch::functor&, const RObject&, signature_t...)>;

        using lambda_rt = std::function<std::any(const dispatch::functor&, const RObject&, signature_t...)>;

        std::vector<lambda_rt> m_rhop = {};

        std::vector<lambda_vt> m_vhop = {};

        std::vector<const dispatch::functor*> m_functors = {};
        
        error m_init_err = error::InvalidCaller;

        void set_init_error(error p_err) {
            m_init_err = p_err;
        }
        
        GETTER_REF(std::vector<lambda_rt>, _rhop, m_rhop)
        GETTER_REF(std::vector<lambda_vt>, _vhop, m_vhop)
        GETTER_REF(std::vector<const dispatch::functor*>, _overloads, m_functors)

        template<class, class ...>
        friend struct detail::HopMethod;

        static_assert((!std::is_reference_v<signature_t> && ...),
                      "rtl::method<...>: any type cannot be specified as reference here.");
    };
}