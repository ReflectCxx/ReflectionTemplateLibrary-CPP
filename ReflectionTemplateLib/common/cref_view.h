#pragma once

/**
 * @brief A lightweight immutable view of a const T object.
 *
 * cref_view<T> provides uniform access to either:
 * - a non-owning const reference (borrowed), or
 * - an internally stored const value (owned).
 *
 * Clients should treat this as a non-owning view: the semantics
 * are always read-only, and ownership is abstracted away.
 *
 * This is useful when you want to accept inputs that may either
 * be passed by reference or value, without worrying about
 * ownership or lifetime in the caller code.
 *
 * ----------------------------------------------------------------------------
 * Purpose:
 *   cref_view is specifically designed to provide read-only access to values
 *   reflected by an RObject. It abstracts whether the value is owned or
 *   referenced, allowing seamless access in both cases.
 *
 * Lifetime:
 *   A cref_view instance is only valid as long as the associated RObject
 *   from which it was obtained remains alive. If the RObject is destroyed,
 *   any cref_view referencing its data becomes invalid and must not be used.
 * ----------------------------------------------------------------------------
 */

#include <optional>

namespace rtl {

    template<class _asType>
    class cref_view
    {
    /*  only constructed if we own the value.
    *   order matters: m_value must be declared before m_cref
    *   because m_cref may bind to m_value during initialization
    */  const std::optional<const _asType> m_value;

        const _asType& m_cref;

    public:

    //  Construct from reference (no copy, no default init)
        cref_view(const _asType& ref) : m_value(std::nullopt), m_cref(ref) {}

    //  Construct from value (copy or move)
        cref_view(_asType&& val) : m_value(std::move(val)), m_cref(*m_value) {}

    //  Default copy and move constructors are OK for an immutable type
        cref_view(cref_view&&) = default;
        cref_view(const cref_view&) = default;
        
    //  Delete copy and move assignment to guarantee no mutation after construction
        cref_view& operator=(cref_view&&) = delete;
        cref_view& operator=(const cref_view&) = delete;

        operator const _asType& () const {
            return m_cref;
        }

        const _asType& get() const {
            return m_cref;
        }
    };
}