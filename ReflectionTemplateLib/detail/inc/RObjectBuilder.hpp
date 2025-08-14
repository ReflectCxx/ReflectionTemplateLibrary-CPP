/*_________________________________________________________________________
* Copyright 2025 Neeraj Singh
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
___________________________________________________________________________*/

#pragma once

#include "RObject.hpp"
#include "RObjectUPtr.h"
#include "RObjectBuilder.h"

namespace rtl::detail {

    inline const std::size_t RObjectBuilder::rtlManagedInstanceCount()
    {
        return access::RObject::m_rtlManagedInstancesCount;
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
            _T* objPtr = static_cast<_T*>(pVal);
            const RObjectId& robjId = RObjectId::create<std::unique_ptr<_T>, _allocOn>(pIsConstCastSafe);
            return access::RObject(std::any(RObjectUPtr<_T>(std::unique_ptr<_T>(objPtr))), buildCloner<_T>(), robjId);
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
                    using U = traits::std_wrapper<_T>::value_type;
                    return access::RObject(std::any(RObjectUPtr<U>(std::move(pVal))), buildCloner<_T>(), robjId);
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