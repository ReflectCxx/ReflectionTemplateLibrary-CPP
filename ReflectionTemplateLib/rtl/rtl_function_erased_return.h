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
    class function<Return(signature_t...)>
    {
        using lambda_vt = std::function<void(const dispatch::functor&, signature_t...)>;

        using lambda_rt = std::function<std::any(const dispatch::functor&, signature_t...)>;

        error m_init_err = error::InvalidCaller;

        std::vector<lambda_rt> m_rhop = {};

        std::vector<lambda_vt> m_vhop = {};

        std::vector<const dispatch::functor*> m_functors = {};

        void set_init_error(error p_err);

        GETTER_REF(std::vector<lambda_rt>, _rhop, m_rhop)
        GETTER_REF(std::vector<lambda_vt>, _vhop, m_vhop)
        GETTER_REF(std::vector<const dispatch::functor*>, _overloads, m_functors)

    public:

        enum call_by {
            value = 0,
            cref = 1,   //const ref.
            ncref = 2   //non-const ref.
        };

        GETTER(rtl::error, _init_error, m_init_err)

        constexpr operator bool() const noexcept;

        constexpr bool must_bind_refs() const noexcept;

        template<class ...args_t>
            requires (sizeof...(args_t) == sizeof...(signature_t))
        constexpr Return operator()(args_t&&...params) const noexcept;

        template<class ...fwd_args_t>
        struct perfect_fwd
        {
            const function<Return(signature_t...)>& fn;
            
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
                                fn.m_vhop[index](*fn.m_functors[index], std::forward<args_t>(params)...);
                                return { error::None, RObject{} };
                            }
                            else
                            {
                                return { error::None,
                                         RObject{ fn.m_rhop[index](*fn.m_functors[index], std::forward<args_t>(params)...),
                                                  fn.m_functors.back()->get_robject_id(), nullptr
                                         }
                                };
                            }
                        }
                    }
                }
                return { error::RefBindingMismatch, RObject{} };
            }
        };

        template<class ...args_t>
            requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind() const noexcept;

        template<detail::member, class ...>
        friend struct detail::HopFunction;

        static_assert((!std::is_reference_v<signature_t> && ...),
            "rtl::function<...>: any type cannot be specified as reference here");
    };
}


namespace rtl
{
    template<class ...signature_t>
    struct static_method<Return(signature_t...)> : function<Return(signature_t...)>
    { 
        template<detail::member, class ...>
        friend struct detail::HopFunction;
    };
}