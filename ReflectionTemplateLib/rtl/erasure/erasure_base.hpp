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

#include "erasure_base.h"
#include "erase_return_n_target.h"
#include "erase_return_aware_target.h"
#include "erase_target_aware_return.h"

namespace rtl::dispatch
{
    template<class record_t, class ...signature_t>
    inline constexpr const erasure_base::e_ret_a_target_t<record_t, signature_t...>&
    erasure_base::to_erased_return_aware_target() const
    {
        auto& erased_record = static_cast<const erase_return_n_target<signature_t...>&>(*this);
        return erased_record.template to_erased_return<record_t>();
    }

    template<class return_t, class ...signature_t>
    inline constexpr const erasure_base::e_target_a_ret_t<return_t, signature_t...>&
    erasure_base::to_erased_target_aware_return() const
    {
        auto& erased_record = static_cast<const erase_return_n_target<signature_t...>&>(*this);
        return erased_record.template to_erased_record<return_t>();
    }
}