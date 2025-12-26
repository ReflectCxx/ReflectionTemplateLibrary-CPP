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

#include "rtl_forward_decls.h"

namespace rtl::dispatch
{
    template<class...args_t>
    struct function_lambda<fn_void::no, erase::t_ctor, args_t...> : lambda
    {
        using fptr_t = Return(*)(alloc, traits::normal_sign_t<args_t>&&...);

        const fptr_t& f_ptr() const {
            return m_fptr;
        }

    private:

        void init(const fptr_t& fptr) {
            m_fptr = fptr;
        }

        fptr_t m_fptr;

        template<class, class ...>
        friend struct dispatch::function_ptr;
    };
}


namespace rtl::dispatch
{
    template<class...args_t>
    struct function_lambda<fn_void::no, erase::t_return, args_t...> : lambda
    {
        using fptr_t = Return(*)(const functor&, traits::normal_sign_t<args_t>&&...);

        const fptr_t& f_ptr() const {
            return m_fptr;
        }

    private:

        void init(const fptr_t& fptr) {
            m_fptr = fptr;
        }

        fptr_t m_fptr;

        template<class, class ...>
        friend struct dispatch::function_ptr;
    };
}


namespace rtl::dispatch
{
    template<class...args_t>
    struct function_lambda<fn_void::yes, erase::t_method, args_t...> : lambda
    {
        using fptr_t = void(*)(const functor&, const RObject&, traits::normal_sign_t<args_t>&&...);
        
        fptr_t f_ptr() const {
            return m_fptr;
        }

    private:
        
        void init(fptr_t fptr) {
            m_fptr = fptr;
        }
        
        fptr_t m_fptr;
        
        template<class, class, class ...>
        friend struct dispatch::method_ptr;
    };
}


namespace rtl::dispatch
{
    template<class...args_t>
    struct function_lambda<fn_void::no, erase::t_method, args_t...> : lambda
    {
        using fptr_t = std::any(*)(const functor&, const RObject&, traits::normal_sign_t<args_t>&&...);
        
        const fptr_t& f_ptr() const {
            return m_fptr;
        }
    
    private:
        
        void init(const fptr_t& fptr) {
            m_fptr = fptr;
        }
        
        fptr_t m_fptr;
        
        template<class, class, class ...>
        friend struct dispatch::method_ptr;
    };
}