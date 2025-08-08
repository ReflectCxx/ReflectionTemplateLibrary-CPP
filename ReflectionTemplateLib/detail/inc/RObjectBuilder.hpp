#pragma once

#include "RObjectBuilder.h"
#include "RObject.hpp"

namespace rtl::detail {

    inline const std::size_t RObjectBuilder::reflectedInstanceCount()
    {
        return access::RObject::m_rtlOwnedHeapAllocCount;
    }

    template<class T, alloc _allocOn, traits::enable_if_std_wrapper<T>>
    inline access::RObject RObjectBuilder::build(T&& pVal)
    {
        return createWithWrapper(std::forward<T>(pVal));
    }

    template<class T, alloc _allocOn, traits::enable_if_not_std_wrapper<T>>
    inline access::RObject RObjectBuilder::build(T&& pVal)
    {
        return create<T, _allocOn>(std::forward<T>(pVal));
    }

    template<class W>
    inline access::RObject RObjectBuilder::createWithWrapper(W&& pWrapper)
    {
        using _W = traits::std_wrapper<traits::base_t<W>>;
        const RObjectId& robjId = RObjectId::createForWrapper<W>();

        if constexpr (_W::type == Wrapper::Unique)
        {
            using _T = _W::innerT;
            const _T* objPtr = pWrapper.release();
            std::function<void(_T*)> deleter = pWrapper.get_deleter();
            return access::RObject(std::any(RObjectPtr(objPtr, deleter)), nullptr, robjId);
        }
        else if constexpr (_W::type == Wrapper::Shared)
        {
            return access::RObject(std::any(std::forward<W>(pWrapper)), nullptr, robjId);
        }
        return access::RObject();
    }

    
    template<class T, rtl::alloc _allocOn>
    inline access::RObject RObjectBuilder::create(T&& pVal)
    {
        using _T = traits::base_t<T>;
        const RObjectId& robjId = RObjectId::create<T, _allocOn>();

        if constexpr (_allocOn == alloc::Heap)
        {
            const _T* objPtr = static_cast<const _T*>(pVal);
            std::function<void(_T*)> deleter = [](_T* pPtr) { delete pPtr; };
            return access::RObject(std::any(RObjectPtr(objPtr, deleter)), createCloner<_T>(), robjId);
        }
        else if constexpr (std::is_pointer_v<traits::remove_const_n_reference<T>>)
        {
            return access::RObject(std::any(static_cast<const _T*>(pVal)), createCloner<_T>(), robjId);
        }
        else
        {
            static_assert(std::is_copy_constructible_v<_T>, "T must be copy-constructible (std::any requires this).");
            return access::RObject(std::any(std::forward<T>(pVal)), createCloner<_T>(), robjId);
        }
    }


    template<class T>
    inline RObjectBuilder::Cloner RObjectBuilder::createCloner()
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
                    return RObjectBuilder::template build<T, alloc::Stack>(T(srcObj));
                }
                else if (pAllocOn == alloc::Heap) {
                    return RObjectBuilder::template build<const T*, alloc::Heap>(new T(srcObj));
                }
                assert(false && "pAllocOn must never be anything else other than alloc::Stack/Heap here.");
            }
            return access::RObject(); //dead code. compiler warning ommited.
        };
    }
}