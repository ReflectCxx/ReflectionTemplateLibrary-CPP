#pragma once

#include <memory>
#include <atomic>
#include <functional>

#include "view.h"
#include "TypeId.h"
#include "RObjectId.h"
#include "rtl_traits.h"

namespace rtl::detail
{
    struct RObjectBuilder;

    template <class T>
    struct RObjectPtr;
}

namespace rtl::access
{
    class Function;

    //Reflecting the object within.
    class RObject
    {
        using Cloner = std::function<RObject(error&, const RObject&, rtl::alloc)>;

        Cloner m_getClone;
        std::any m_object;
        detail::RObjectId m_objectId;

        static std::atomic<std::size_t> m_rtlOwnedHeapAllocCount;

        RObject(const RObject&) = default;
        RObject(std::any&& pObject, Cloner&& pCloner, const detail::RObjectId& pRObjectId);

        template <class T>
        const T* extract() const;

        std::size_t getConverterIndex(const std::size_t pToTypeId) const;

        template <rtl::alloc _allocOn>
        std::pair<error, RObject> createCopy() const;

        template<class T>
        std::optional<rtl::view<T>> performConversion(const std::size_t pIndex) const;

    public:

        ~RObject() = default;
        RObject() = default;
        RObject(RObject&&) noexcept;
        RObject& operator=(RObject&&) = delete;
        RObject& operator=(const RObject&) = delete;

        GETTER(std::size_t, TypeId, m_objectId.m_typeId)
        GETTER_BOOL(Empty, (m_object.has_value() == false))
        GETTER_BOOL(OnHeap, (m_objectId.m_allocatedOn == alloc::Heap))
        GETTER_BOOL(RefOrPtr, (m_objectId.m_isPointer == IsPointer::Yes))
        GETTER_BOOL(Const, m_objectId.m_isTypeConst) // Objects created through reflection are treated mutable by default.

        template<rtl::alloc _allocOn>
        std::pair<error, RObject> clone() const;

        template <class _asType>
        bool canViewAs() const;

        template <class T, traits::enable_if_raw_pointer<T> = 0>
        std::optional<rtl::view<T>> view() const;

        template <class T, traits::enable_if_std_wrapper<T> = 0>
        std::optional<rtl::view<T>> view() const;

        template<class T, traits::enable_if_not_std_wrapper_or_raw_ptr<T> = 0>
        std::optional<rtl::view<T>> view() const;

        //friends :)
        template <class T>
        friend struct detail::RObjectPtr;
        friend detail::RObjectBuilder;
    };
}