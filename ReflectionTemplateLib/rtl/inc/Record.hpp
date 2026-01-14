/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <inc/Record.h>
#include <dispatch/function_ptr.h>
#include <rtl_constructor.h>

namespace rtl
{
    template<>
    inline constructor<> Record::ctor() const
    {
        constructor<> fnCtor;
        auto strictId = traits::uid<traits::strict_sign_id_t<alloc>>::value;
        const auto& method = m_methods.at(detail::ctor_name(m_recordName));

        for (auto& ty_meta : method.getFunctorsMeta())
        {
            if (strictId == ty_meta.get_strict_args_id()) 
            {
                using ctor_t = dispatch::function_ptr<Return, alloc>;
                auto fptr = static_cast<const ctor_t&>(ty_meta.get_functor()).f_ptr();
                fnCtor.get_hop().push_back(fptr);
                fnCtor.get_overloads().push_back(&ty_meta.get_functor());
                fnCtor.set_init_error(error::None);
                break;
            }
        }
        return fnCtor;
    }


    template<class ...args_t>
    inline constructor<args_t...> Record::ctor() const
    {
        std::vector<rtl::type_meta> fnTyMetas(detail::call_by::ncref);
        auto normalId = traits::uid<traits::normal_sign_id_t<args_t...>>::value;
        const auto& method = m_methods.at(detail::ctor_name(m_recordName));

        for (auto& ty_meta : method.getFunctorsMeta())
        {
            if (normalId == ty_meta.get_normal_args_id())
            {
                if (normalId == ty_meta.get_strict_args_id()) {
                    fnTyMetas[detail::call_by::value] = ty_meta;
                }
                else if (!ty_meta.is_any_arg_ncref()) {
                    fnTyMetas[detail::call_by::cref] = ty_meta;
                }
                else fnTyMetas.push_back(ty_meta);
            }
        }

        constructor<args_t...> fnCtor;
        for (auto& ty_meta : fnTyMetas)
        {
            if (ty_meta.is_empty()) {
                fnCtor.get_hop().push_back(nullptr);
                fnCtor.get_overloads().push_back(nullptr);
                continue;
            }

            using fn_cast = dispatch::functor_cast<traits::normal_sign_t<args_t>...>;
            auto fn = fn_cast(ty_meta.get_functor()).template to_function<dispatch::erase::t_ctor>();

            fnCtor.get_hop().push_back(fn.f_ptr());
            fnCtor.get_overloads().push_back(&ty_meta.get_functor());
            fnCtor.set_init_error(error::None);
        }

        if (fnCtor.get_init_error() != error::None) {
            fnCtor.set_init_error(error::SignatureMismatch);
        }
        return fnCtor;
    }
}