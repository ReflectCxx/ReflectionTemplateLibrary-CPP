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

#include <inc/RObject.hpp>
#include <detail/inc/RObjectUPtr.h>
#include <detail/inc/RObjectBuilder.h>

namespace rtl::detail 
{
    template<class T>
    struct Cloner
    {
        static Return copyCtor(alloc p_alloc_on, const RObject& p_other)
        {
            if constexpr (std::is_copy_constructible_v<T>)
            {
                const auto& srcObj = p_other.view<T>()->get();
                switch (p_alloc_on)
                {
                case alloc::Stack:
                    return {
                        error::None,
                        RObjectBuilder<T>::template build<alloc::Stack>(T(srcObj), &copyCtor, true)
                    };
                case alloc::Heap:
                    return {
                        error::None,
                        RObjectBuilder<T*>::template build<alloc::Heap>(new T(srcObj), &copyCtor, true)
                    };
                default:
                    return { error::EmptyRObject, RObject{} };
                }
            }
            else
            {
                return { error::TypeNotCopyConstructible, RObject{} };
            }
        }
    };
}


namespace rtl::detail 
{
    template<class T>
    template<rtl::alloc _allocOn> requires (_allocOn == alloc::Heap)
    inline RObject RObjectBuilder<T>::build(T&& pVal, traits::cloner_t pClonerFn, bool pIsConstCastSafe) noexcept
    {
        using _T = traits::raw_t<T>;
        return RObject( std::any{
                            std::in_place_type<RObjectUPtr<_T>>,
                            RObjectUPtr<_T>(std::unique_ptr<_T>(static_cast<_T*>(pVal)))
                        },
                        RObjectId::create<std::unique_ptr<_T>, alloc::Heap>(pIsConstCastSafe, pClonerFn) );
    }


    template<class T>
    template <rtl::alloc _allocOn>
    inline RObject rtl::detail::RObjectBuilder<T>::build(T&& pVal, bool pIsConstCastSafe) noexcept
    {
        using _T = traits::raw_t<T>;
        if constexpr (traits::std_wrapper<_T>::type == Wrapper::None)
        {
            return RObjectBuilder<T>::template build<_allocOn>(
                std::forward<T>(pVal), &Cloner<_T>::copyCtor, pIsConstCastSafe
            );
        }
        else
        {
            return RObjectBuilder<T>::template build<_allocOn>(
                std::forward<T>(pVal), &Cloner<typename traits::std_wrapper<_T>::value_type>::copyCtor, pIsConstCastSafe
            );
        }
    }


    template<class T>
    template<rtl::alloc _allocOn> requires (_allocOn == alloc::Stack)
    inline RObject RObjectBuilder<T>::build(T&& pVal, traits::cloner_t pClonerFn, bool pIsConstCastSafe) noexcept
    {
        using _T = traits::raw_t<T>;
        constexpr bool isRawPointer = std::is_pointer_v<traits::remove_cref_t<T>>;

        if constexpr (isRawPointer)
        {
            return RObject( std::any { static_cast<const _T*>(pVal) },
                            RObjectId::create<T, alloc::Stack>(pIsConstCastSafe, pClonerFn) );
        }
        else
        {
            if constexpr (traits::std_wrapper<_T>::type == Wrapper::Unique)
            {
                using U = traits::std_wrapper<_T>::value_type;
                return RObject( std::any {
                                    std::in_place_type<RObjectUPtr<U>>,
                                    RObjectUPtr<U>(std::move(pVal))
                                },
                                RObjectId::create<T, alloc::Stack>(pIsConstCastSafe, pClonerFn) );
            }
            else
            {
                static_assert(std::is_copy_constructible_v<_T>, "T must be copy-constructible (std::any requires this).");
                return RObject( std::any {
                                    std::in_place_type<T>,
                                    std::forward<T>(pVal)
                                },
                                RObjectId::create<T, alloc::Stack>(pIsConstCastSafe, pClonerFn) );
            }
        }
    }
}