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

#include <utility>

#include "RObject.hpp"
#include "RObjectUPtr.h"
#include "RObjectBuilder.h"

namespace rtl::detail 
{    
    template<class T>
    FORCE_INLINE const std::vector<traits::ConverterPair>& getConverters() noexcept
    {
        // extract wrapper info.
        using _W = traits::std_wrapper<traits::raw_t<T>>;
        // extract Un-Qualified raw type.
        using _T = traits::raw_t<std::conditional_t<(_W::type == Wrapper::None), T, typename _W::value_type>>;
        return rtl::detail::ReflectCast<_T>::getConversions();
    }


    template<class T>
    template <rtl::alloc _allocOn> requires (_allocOn == alloc::Heap)
    FORCE_INLINE RObject RObjectBuilder<T>::build(T&& pVal, std::optional<FunctorId> pClonerId, bool pIsConstCastSafe) noexcept
    {
        using _T = traits::raw_t<T>;
        return RObject( std::any{
                            std::in_place_type<RObjectUPtr<_T>>,
                            RObjectUPtr<_T>(std::unique_ptr<_T>(static_cast<_T*>(pVal)))
                        },
                        RObjectId::create<std::unique_ptr<_T>, alloc::Heap>(pClonerId, pIsConstCastSafe),
                        &getConverters<std::unique_ptr<_T>>());
    }

    
    template<class T>
    template <rtl::alloc _allocOn> requires (_allocOn == alloc::Stack)
    FORCE_INLINE RObject RObjectBuilder<T>::build(T&& pVal, std::optional<FunctorId> pClonerId, bool pIsConstCastSafe) noexcept
    {
        using _T = traits::raw_t<T>;
        constexpr bool isRawPointer = std::is_pointer_v<traits::remove_const_n_ref_t<T>>;

        if constexpr (isRawPointer)
        {
            return RObject( std::any { static_cast<const _T*>(pVal) },
                            RObjectId::create<T, alloc::Stack>(pClonerId, pIsConstCastSafe),
                            &getConverters<T>() );
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
                                RObjectId::create<T, alloc::Stack>(pClonerId, pIsConstCastSafe),
                                &getConverters<T>() );
            }
            else
            {
                static_assert(std::is_copy_constructible_v<_T>, "T must be copy-constructible (std::any requires this).");
                return RObject( std::any {
                                    std::in_place_type<T>,
                                    std::forward<T>(pVal)
                                },
                                RObjectId::create<T, alloc::Stack>(pClonerId, pIsConstCastSafe),
                                &getConverters<T>() );
            }
        }
    }
}