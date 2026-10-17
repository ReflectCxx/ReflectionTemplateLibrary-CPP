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

#include <detail/inc/RObjectUPtr.h>

/**
 * @brief A lightweight immutable view of a const T object.
 *
 * rtl::view<T> provides uniform access to either:
 * - a non-owning const reference (borrowed), or
 * - an internally stored const value (owned).
 *
 * Clients should treat this as a non-owning view: the semantics
 * are always read-only, and ownership is abstracted away.
 * ----------------------------------------------------------------------------
 * Purpose:
 *   rtl::view is specifically designed to provide read-only access to values
 *   reflected by an RObject. It abstracts whether the value is owned or
 *   referenced, allowing seamless access in both cases.
 *
 * Lifetime:
 *   A rtl::view instance is only valid as long as the associated RObject
 *   from which it was obtained remains alive. If the RObject is destroyed,
 *   any rtl::view referencing its data becomes invalid and must not be used.
 * ----------------------------------------------------------------------------
 */

namespace rtl
{
    template<class _asType>
    class view<_asType, std::enable_if_t<traits::is_unique_ptr_v<_asType>> >
    {
        using T = typename traits::std_wrapper<_asType>::value_type;

        const detail::RObjectUPtr<T>& m_uptrRef;

        //_asType move() const {
        //    return std::move(m_uptrRef.release());
        //}

        //friend rtl::RObject;

    public:

        //  Construct from reference (no copy, no default init)
        explicit view(const detail::RObjectUPtr<T>& pUptrRef): m_uptrRef(pUptrRef) { }

        //  Delete all forms of copying and moving, enforcing true immutablilty.
        view(view&&) = delete;
        view(const view&) = delete;
        view& operator=(view&&) = delete;
        view& operator=(const view&) = delete;

        // UPDATE: MOVING DISALLOWED NOW.
	    // cannot move a std::unique_ptr out once its inside rtl::RObject. it can only be viewed.
	    // done for keeping the rtl::view strictly Read-only and a consistent interface.
        const _asType& get() const {
            return m_uptrRef.cref();
        }
    };
}