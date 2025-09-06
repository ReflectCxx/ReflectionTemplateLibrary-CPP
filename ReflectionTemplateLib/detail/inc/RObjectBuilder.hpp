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

namespace rtl::detail {

    inline const std::size_t RObjectBuilder::rtlManagedInstanceCount()
    {
        return RObject::getInstanceCounter();
    }
    
    template<class T>
    inline const std::vector<traits::ConverterPair>& RObjectBuilder::getConverters()
    {
        // extract wrapper info.
        using _W = traits::std_wrapper<traits::raw_t<T>>;
        // extract Un-Qualified raw type.
        using _T = traits::raw_t<std::conditional_t<(_W::type == Wrapper::None), T, typename _W::value_type>>;
        return rtl::detail::ReflectCast<_T>::getConversions();
    }

    template<class T>
    inline const RObjectBuilder::Cloner& RObjectBuilder::buildCloner()
    {
        using W = traits::std_wrapper<T>;
        using _T = std::conditional_t<W::type == Wrapper::None, T, typename W::value_type>;

        if constexpr (std::is_copy_constructible_v<_T>)
        {
            static const Cloner cloner = [](const RObject& pOther, alloc pAllocOn) -> Return
            {
                const auto& srcObj = pOther.view<_T>()->get();
                switch (pAllocOn)
                {
                case alloc::Stack:
                    return { 
                        error::None,
                        RObjectBuilder::template build<_T, alloc::Stack, true>(_T(srcObj))
                    };
                case alloc::Heap:
                    return { 
                        error::None,
                        RObjectBuilder::template build<_T*, alloc::Heap, true>(new _T(srcObj))
                    };
                default:
                    return { 
                        error::EmptyRObject, 
                        RObject{}
                    };
                }
            };
            return cloner;
        }
        else
        {
            static const Cloner cloner = [](const RObject&, alloc) -> Return {
                return {
                    error::TypeNotCopyConstructible, 
                    RObject{} 
                };
            };
            return cloner;
        }
    }



    template<class T, rtl::alloc _allocOn, bool _isConstCastSafe>
    inline RObject RObjectBuilder::build(T&& pVal)
    {
        using _T = traits::raw_t<T>;
        constexpr bool isRawPointer = std::is_pointer_v<traits::remove_const_n_ref_t<T>>;

        if constexpr (_allocOn == alloc::Heap)
        {
            static_assert(isRawPointer, "Invalid 'alloc' specified for non-pointer-type 'T'");
            return RObject(RObjectId::create<std::unique_ptr<_T>, _allocOn, _isConstCastSafe>(),
                           std::any {
                                std::in_place_type<RObjectUPtr<_T>>,
                                RObjectUPtr<_T>(std::unique_ptr<_T>(static_cast<_T*>(pVal))) 
                           },
                           &buildCloner<_T>(),
                           &getConverters<std::unique_ptr<_T>>());
        }
        else if constexpr (_allocOn == alloc::Stack)
        {
            if constexpr (isRawPointer)
            {
                return RObject(RObjectId::create<T, _allocOn, _isConstCastSafe>(),
                               std::any {
                                    static_cast<const _T*>(pVal)
                               },
                               &buildCloner<_T>(),
                               &getConverters<T>());
            }
            else
            {
                if constexpr (traits::std_wrapper<_T>::type == Wrapper::Unique)
                {
                    using U = traits::std_wrapper<_T>::value_type;
                    return RObject(RObjectId::create<T, _allocOn, _isConstCastSafe>(),
                                   std::any {
                                        std::in_place_type<RObjectUPtr<U>>,
                                        RObjectUPtr<U>(std::move(pVal))
                                   },
                                   &buildCloner<_T>(),
                                   &getConverters<T>());
                }
                else
                {
                    static_assert(std::is_copy_constructible_v<_T>, "T must be copy-constructible (std::any requires this).");
                    return RObject(RObjectId::create<T, _allocOn, _isConstCastSafe>(),
                                   std::any {
                                        std::in_place_type<T>,
                                        std::forward<T>(pVal)
                                   },
                                   &buildCloner<_T>(),
                                   &getConverters<T>());
                }
            }
        }
    }
}