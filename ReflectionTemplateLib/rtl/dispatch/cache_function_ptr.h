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

#include <list>

#include "function_ptr.hpp"

namespace rtl::cache
{
    template<class return_t, class ...signature_t>
    struct function_ptr
    {
        using function_t = dispatch::function_ptr<return_t, signature_t...>;

        static const function_ptr& instance()
        {
            static function_ptr instance_;
            return instance_;
        }

        template<detail::member mem_kind, class record_t>
        const dispatch::functor& push_ctor(traits::uid_t p_record_uid, std::size_t lambda_index) const
        {
            m_cache.emplace_back(std::make_pair(function_t(nullptr, p_record_uid, mem_kind), lambda_index));
            function_t& fn = m_cache.back().first;
            fn.template init_lambda<mem_kind, record_t>();
            return fn;
        }

        const dispatch::functor& push(return_t(*fptr)(signature_t...), traits::uid_t p_record_uid, 
                                      detail::member member_kind, std::size_t lambda_index) const
        {
            m_cache.emplace_back(std::make_pair(function_t(fptr, p_record_uid, member_kind), lambda_index));
            
            function_t& fn = m_cache.back().first;
            if (member_kind == detail::member::None || member_kind == detail::member::Static) {
                fn.init_lambda();
            }
            return fn;
        }

        std::pair<dispatch::functor*, std::size_t> find(return_t(*fptr)(signature_t...)) const
        {
            for (auto& itr : m_cache)
            {
                const auto& functor = itr.first;
                if (functor.is_same(fptr)) {
                    return { &itr.first, itr.second };
                }
            }
            return { nullptr, rtl::index_none };
        }

        function_ptr(function_ptr&&) = delete;
        function_ptr(const function_ptr&) = delete;
        function_ptr& operator=(function_ptr&&) = delete;
        function_ptr& operator=(const function_ptr&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<std::pair<function_t, std::size_t>> m_cache;

        function_ptr() = default;
    };
}