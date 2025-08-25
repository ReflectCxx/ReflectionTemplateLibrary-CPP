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

#include "RObject.hpp"
#include "RObjectUPtr.h"
#include "RObjectBuilder.h"

namespace rtl::detail {

    inline const std::size_t RObjectBuilder::rtlManagedInstanceCount()
    {
        return RObject::getInstanceCounter();
    }
    

    template<class T>
    inline RObjectBuilder::Cloner RObjectBuilder::buildCloner()
    {
        using W = traits::std_wrapper<T>;
        using _T = std::conditional_t<W::type == Wrapper::None, T, typename W::value_type>;

        if constexpr (std::is_copy_constructible_v<_T>)
        {
            return [](error& pError, const RObject& pOther, alloc pAllocOn)-> RObject
            {
                const auto& srcObj = pOther.view<_T>()->get();
                pError = error::None;
                if (pAllocOn == alloc::Stack) {
                    return RObjectBuilder::template build<_T, alloc::Stack>(_T(srcObj), true);
                }
                else if (pAllocOn == alloc::Heap) {
                    return RObjectBuilder::template build<_T*, alloc::Heap>(new _T(srcObj), true);
                }
                return RObject(); //dead code. compiler warning ommited.
            };
        }
        else 
        {
            return [](error& pError, const RObject& pOther, alloc pAllocOn)-> RObject
            {
                pError = error::TypeNotCopyConstructible;
                return RObject();
            };
        }
    }


    template<class T, rtl::alloc _allocOn>
    inline RObject RObjectBuilder::build(T&& pVal, const bool pIsConstCastSafe)
    {
        using _T = traits::raw_t<T>;
        constexpr bool isRawPointer = std::is_pointer_v<traits::remove_const_n_ref_t<T>>;

        if constexpr (_allocOn == alloc::Heap)
        {
            static_assert(isRawPointer, "Invalid 'alloc' specified for non-pointer-type 'T'");
            _T* objPtr = static_cast<_T*>(pVal);
            const RObjectId& robjId = RObjectId::create<std::unique_ptr<_T>, _allocOn>(pIsConstCastSafe);
            return RObject(std::any(RObjectUPtr<_T>(std::unique_ptr<_T>(objPtr))), buildCloner<_T>(), robjId);
        }
        else if constexpr (_allocOn == alloc::Stack)
        {
            if constexpr (isRawPointer)
            {
                const RObjectId& robjId = RObjectId::create<T, _allocOn>(pIsConstCastSafe);
                return RObject(std::any(static_cast<const _T*>(pVal)), buildCloner<_T>(), robjId);
            }
            else
            {
                const RObjectId& robjId = RObjectId::create<T, _allocOn>(pIsConstCastSafe);
                if constexpr (traits::std_wrapper<_T>::type == Wrapper::Unique)
                {
                    using U = traits::std_wrapper<_T>::value_type;
                    return RObject(std::any(RObjectUPtr<U>(std::move(pVal))), buildCloner<_T>(), robjId);
                }
                else 
                {
                    static_assert(std::is_copy_constructible_v<_T>, "T must be copy-constructible (std::any requires this).");
                    return RObject(std::any(std::forward<T>(pVal)), buildCloner<_T>(), robjId);
                }
            }
        }
    }
}