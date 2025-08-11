#pragma once

#include "RObjectBuilder.h"
#include "RObject.hpp"

namespace rtl::detail {

    inline const std::size_t RObjectBuilder::reflectedInstanceCount()
    {
        return access::RObject::m_rtlOwnedHeapAllocCount;
    }
    

    template<class T>
    inline RObjectBuilder::Cloner RObjectBuilder::buildCloner()
    {
        return [](error& pError, const access::RObject& pOther, alloc pAllocOn)-> access::RObject
        {
            if constexpr (!std::is_copy_constructible_v<T>)
            {
                pError = error::Instantiating_typeNotCopyConstructible;
                return access::RObject();
            }
            else
            {
                pError = error::None;
                const auto& srcObj = pOther.view<T>()->get();
                if (pAllocOn == alloc::Stack) {
                    return RObjectBuilder::template build<T, alloc::Stack>(T(srcObj), true);
                }
                else if (pAllocOn == alloc::Heap) {
                    return RObjectBuilder::template build<T*, alloc::Heap>(new T(srcObj), true);
                }
                assert(false && "pAllocOn must never be anything else other than alloc::Stack/Heap here.");
            }
            return access::RObject(); //dead code. compiler warning ommited.
        };
    }


    template<class T, rtl::alloc _allocOn>
    inline access::RObject RObjectBuilder::build(T&& pVal, const bool pIsConstCastSafe)
    {
        using _T = traits::raw_t<T>;
        constexpr bool isRawPointer = std::is_pointer_v<traits::remove_const_n_ref_t<T>>;

        if constexpr (_allocOn == alloc::Heap)
        {
            static_assert(isRawPointer, "Invalid 'alloc' specified for non-pointer-type 'T'");
            const RObjectId& robjId = RObjectId::create<std::unique_ptr<const _T>, _allocOn>(pIsConstCastSafe);
            return access::RObject(std::any(std::shared_ptr<const _T>(pVal)), buildCloner<_T>(), robjId);
        }
        else if constexpr (_allocOn == alloc::Stack)
        {
            if constexpr (isRawPointer)
            {
                const RObjectId& robjId = RObjectId::create<T, _allocOn>(pIsConstCastSafe);
                return access::RObject(std::any(static_cast<const _T*>(pVal)), buildCloner<_T>(), robjId);
            }
            else
            {
                const RObjectId& robjId = RObjectId::create<T, _allocOn>(pIsConstCastSafe);
                if constexpr (traits::std_wrapper<_T>::type == Wrapper::Unique) 
                {
                    using V = traits::std_wrapper<_T>::value_type;
                    std::shared_ptr<V> sptr = std::move(pVal);
                    return access::RObject(std::any(std::move(sptr)), nullptr, robjId);
                }
                else 
                {
                    static_assert(std::is_copy_constructible_v<_T>, "T must be copy-constructible (std::any requires this).");
                    return access::RObject(std::any(std::forward<T>(pVal)), buildCloner<_T>(), robjId);
                }
            }
        }
    }
}