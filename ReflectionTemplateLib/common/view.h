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

#include <optional>

namespace rtl {

    template<class _asType>
    class view
    {
    /*  only constructed if we own the value.
    *   order matters: m_value must be declared before m_cref
    *   because m_cref may bind to m_value during initialization
    */  const std::optional<_asType> m_value;

        const _asType& m_cref;

    public:

    //  Construct from reference (no copy, no default init)
        view(const _asType& ref) : m_value(std::nullopt), m_cref(ref) {}

    //  Construct from value (copy or move)
        view(_asType&& val) : m_value(std::move(val)), m_cref(*m_value) {}

    //  Delete all forms of copying and moving, enforcing true immutablilty.
        view(view&&) = delete;
        view(const view&) = delete;
        view& operator=(view&&) = delete;
        view& operator=(const view&) = delete;

        const _asType& get() const {
            return m_cref;
        }
    };
}