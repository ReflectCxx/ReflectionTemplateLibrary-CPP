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

#include <functional>

#include "RObject.h"

namespace rtl::detail 
{
    template <class T>
    struct RObjectPtr
    {
        const T* m_ptr;
        std::function<void(T*)> m_deleter;

        RObjectPtr() = default;
        RObjectPtr(const RObjectPtr&) = default;

        RObjectPtr(const T* pPtr, const std::function<void(T*)>& pDeleter)
            : m_ptr(pPtr)
            , m_deleter(pDeleter)
        {
        }

        ~RObjectPtr() {
            if (m_deleter) {
                m_deleter(const_cast<T*>(m_ptr));
                access::RObject::m_rtlOwnedHeapAllocCount.fetch_sub(1);
                assert(access::RObject::m_rtlOwnedHeapAllocCount >= 0 && "Disaster: rtlOwnedHeapAllocCount cannot be less than 0");
            }
        }

        RObjectPtr(RObjectPtr&& pOther) noexcept
            : m_ptr(std::move(pOther.m_ptr))
            , m_deleter(std::move(pOther.m_deleter)) {
            pOther.m_deleter = nullptr;
        }
    };
}