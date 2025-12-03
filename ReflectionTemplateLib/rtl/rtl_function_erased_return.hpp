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

#include "rtl_function_erased_return.h"

namespace rtl
{
    template<class ...signature_t>
    inline void function<Return(signature_t...)>::set_init_error(error p_err) {
        m_init_err = p_err;
    }

    template<class ...signature_t>
    inline constexpr function<Return(signature_t...)>::operator bool() const noexcept {
        return !(m_init_err != error::None || m_functors.empty() ||
            (m_functors.size() == 1 && m_functors[0] == nullptr));
    }


    template<class ...signature_t>
    inline constexpr bool function<Return(signature_t...)>::must_bind_refs() const noexcept {
        return (m_functors[call_by::value] == nullptr &&
            (m_functors.size() > call_by::ncref || m_functors[call_by::cref]->is_any_arg_ncref()));
    }


    template<class ...signature_t>
    template<class ...args_t> 
        requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
    inline constexpr const function<Return(signature_t...)>::perfect_fwd<args_t...>
                    function<Return(signature_t...)>::bind() const noexcept {
        return perfect_fwd<args_t...>{ *this };
    }


	template<class ...signature_t>
	template<class ...args_t>
        requires (sizeof...(args_t) == sizeof...(signature_t))
	[[nodiscard]] [[gnu::hot]] [[gnu::flatten]]
	inline constexpr Return function<Return(signature_t...)>::operator()(args_t&&...params) const noexcept
	{
        if (!(*this)) [[unlikely]] {
            return { m_init_err, RObject{} };
        }

        if (must_bind_refs()) [[unlikely]] {
            return { error::ExplicitRefBindingRequired, RObject{} };
        }

        auto index = (m_functors[call_by::value] != nullptr ? call_by::value : call_by::cref);
        if (m_functors[index]->is_void())
        {
            m_vhop[index](*m_functors[index], std::forward<args_t>(params)...);
            return { error::None, RObject{} };
        }
        else
        {
            return { error::None,
                     RObject{ m_rhop[index](*m_functors[index], std::forward<args_t>(params)...),
                              m_functors.back()->get_robject_id(), nullptr
                     }
            };
        }
	}
}