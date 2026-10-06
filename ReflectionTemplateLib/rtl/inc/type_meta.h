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

#include <dispatch/functor.h>

namespace rtl
{
    struct type_meta
    {
        type_meta(const dispatch::functor& p_functor)
            : m_functor(p_functor)
        { }

        type_meta() = default;
        type_meta(type_meta&&) = default;
        type_meta(const type_meta&) = default;
        type_meta& operator=(type_meta&&) = default;
        type_meta& operator=(const type_meta&) = default;
        const bool operator==(const type_meta& pOther) const;

        constexpr const bool is_void() const;
        constexpr const bool is_empty() const;
        constexpr const bool is_any_arg_ncref() const;

        constexpr const std::string get_signature_str() const;
        constexpr const std::vector<std::size_t>& get_args_id_arr() const;

        constexpr const detail::member get_member_kind() const;
        constexpr const dispatch::functor& get_functor() const;

        constexpr const traits::uid_t get_record_id() const;
        constexpr const traits::uid_t get_return_id() const;
        constexpr const traits::uid_t get_normal_args_id() const;
        constexpr const traits::uid_t get_strict_args_id() const;


        template<class return_t, class ...signature_t>
        static type_meta add_function(return_t(*p_fptr)(signature_t...),
                                      traits::uid_t p_record_uid, detail::member p_member_kind);

        template<class record_t, class return_t, class ...signature_t>
        static type_meta add_method(return_t(record_t::* p_fptr)(signature_t...));

        template<class record_t, class return_t, class ...signature_t>
        static type_meta add_method(return_t(record_t::* p_fptr)(signature_t...) const);

        template<detail::member mem_kind, class record_t, class return_t, class ...signature_t>
        static type_meta add_constructor();

    private:

        using functor_t = std::optional<std::reference_wrapper<const dispatch::functor>>;

        functor_t m_functor = std::nullopt;

        friend detail::CxxReflection;
    };
}


namespace rtl
{
    constexpr const bool type_meta::is_empty() const {
        return !m_functor.has_value();
    }

    constexpr const bool type_meta::is_void() const {
        return m_functor->get().m_is_void;
    }

    constexpr const bool type_meta::is_any_arg_ncref() const {
        return m_functor->get().m_is_any_arg_ncref;
    }

    constexpr const std::string type_meta::get_signature_str() const {
        return m_functor->get().m_signature_str;
    }

    constexpr const traits::uid_t type_meta::get_return_id() const {
        return m_functor->get().m_return_id;
    }

    constexpr const traits::uid_t type_meta::get_record_id() const {
        return m_functor->get().m_record_id;
    }

    constexpr const traits::uid_t type_meta::get_normal_args_id() const {
        return m_functor->get().m_normal_args_id;
    }

    constexpr const traits::uid_t type_meta::get_strict_args_id() const {
        return m_functor->get().m_strict_args_id;
    }

    constexpr const detail::member type_meta::get_member_kind() const {
        return m_functor->get().m_member_kind;
    }

    constexpr const dispatch::functor& type_meta::get_functor() const {
        return m_functor->get();
    }

    constexpr const std::vector<std::size_t>& type_meta::get_args_id_arr() const {
        return m_functor->get().m_args_type_ids;
    }

    inline const bool type_meta::operator==(const type_meta& pOther) const
    {
        return (!is_empty() && !pOther.is_empty() &&
                get_functor().m_return_id == pOther.get_functor().m_return_id &&
                get_functor().m_record_id == pOther.get_functor().m_record_id &&
                get_functor().m_strict_args_id == pOther.get_functor().m_strict_args_id &&
                get_functor().m_member_kind == pOther.get_functor().m_member_kind);
    }
}