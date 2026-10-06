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

#include <inc/RObject.h>

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

#include <cassert>

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
            RObject::getInstanceCounter()++;//.fetch_add(1, std::memory_order_relaxed);
        }

        // Destructor: decrements allocation count if we still own the object.
        ~RObjectUPtr() {
            if (m_uniquePtr) {
                RObject::getInstanceCounter()--;//.fetch_sub(1, std::memory_order_relaxed);
            }
        }

        const T* get() const {
            return m_uniquePtr.get();
        }

        const std::unique_ptr<T>& cref() const {
            return m_uniquePtr;
        }

    private:

        mutable std::unique_ptr<T> m_uniquePtr;
    };
}