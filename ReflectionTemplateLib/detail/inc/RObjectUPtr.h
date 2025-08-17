/*_________________________________________________________________________
* Copyright 2025 Neeraj Singh (reflectcxx@outlook.com)
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
#include <memory>
#include <cassert>
#include <utility>
#include <functional>

#include "RObject.h"

/*------------------------------------------------------------------------------------------
    RObjectUPtr<T>

    Purpose:
    --------
    MSVC's std::any refuses to store std::unique_ptr<T> directly because
    std::unique_ptr is *not copy-constructible*. This restriction makes sense
    for safety, but it prevents us from using std::any to hold unique_ptr-managed
    objects in a reflection context.

    GCC/Clang technically allow it in certain cases by relying on moves, but
    their behavior isn't guaranteed consistent across all standards.
    We need *predictable cross-compiler behavior*.

    Solution:
    ---------
    RObjectUPtr<T> is a thin, move-only wrapper that *pretends* to be copyable,
    but its "copy constructor" does nothing and RTL makes sure its never called.
    This satisfies std::any's requirement for a copy constructor, while ensuring
    only one instance ever truly owns the resource.

    Key Properties:
    ---------------
    1. Copy constructor - never gets called.
    2. Move constructor works as expected.
    3. Deleted copy/move assignment operators to prevent post-construction reassignment.
    4. Tracks heap allocation count via RObject's internal counter for lifetime diagnostics.

--------------------------------------------------------------------------------------------*/

namespace rtl::detail
{
    template <class T>
    struct RObjectUPtr
    {
        RObjectUPtr() = delete;
        RObjectUPtr& operator=(const RObjectUPtr&) = delete;
        RObjectUPtr& operator=(RObjectUPtr&& other) = delete;

        // Copy constructor: empty, just to trick the 'std::any'. NEVER GETS CALLED!!
        RObjectUPtr(const RObjectUPtr& pOther) {
            assert(false && "RObjectUPtr(const RObjectUPtr&) must never get called.");
        }

        // Move constructor: transfers ownership as usual.
        RObjectUPtr(RObjectUPtr&& pOther) noexcept
            : m_uniquePtr(std::move(pOther.m_uniquePtr)) {
            pOther.m_uniquePtr = nullptr;
        }

        // Construct directly from std::unique_ptr<T>, tracking RTL-owned heap allocations.
        RObjectUPtr(std::unique_ptr<T>&& pUniquePtr)
            : m_uniquePtr(std::move(pUniquePtr)) {
            access::RObject::m_rtlManagedInstancesCount.fetch_add(1, std::memory_order_relaxed);
        }

        // Destructor: decrements allocation count if we still own the object.
        ~RObjectUPtr() {
            if (m_uniquePtr) {
                access::RObject::m_rtlManagedInstancesCount.fetch_sub(1, std::memory_order_relaxed);
            }
        }

        const T* get() const {
            return m_uniquePtr.get();
        }

        std::unique_ptr<T> release() const 
        {
            if (m_uniquePtr) {
                access::RObject::m_rtlManagedInstancesCount.fetch_sub(1, std::memory_order_relaxed);
                return std::move(m_uniquePtr);
            }
            return nullptr;
        }

    private:

        mutable std::unique_ptr<T> m_uniquePtr;
    };
}