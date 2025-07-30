#pragma once

#include <memory>
#include <functional>

#include "view.h"
#include "TypeId.h"
#include "RObjectId.h"
#include "Constants.h"
#include "rtl_traits.h"

namespace rtl::detail 
{
    class RObjectBuilder;
}

namespace rtl::access
{
    class Function;

    //Reflecting the object within.
    class RObject
    {
        std::any m_object;
        std::any m_wrapper;
        std::shared_ptr<void> m_deallocator;
        detail::RObjectId m_objectId;

        RObject(const RObject&) = default;

        RObject(std::any&& pObject, std::any&& pWrapper,
                std::shared_ptr<void>&& pDeleter, const detail::RObjectId& pRObjectId);

        template<class T>
        const T& as(bool pGetFromWrapper = false) const;

        std::size_t getConverterIndex(const std::size_t pToTypeId) const;

        template <class W>
        static RObject create(W&& pWrapper, rtl::alloc pAllocOn);

        template <class T>
        static RObject create(T&& pVal, std::shared_ptr<void>&& pDeleter, rtl::alloc pAllocOn);

    public:

        RObject() = default;
        RObject(RObject&&) noexcept;

        ~RObject() = default;

        RObject& operator=(RObject&&) = delete;
        RObject& operator=(const RObject&) = delete;

        GETTER(std::any,,m_object)
        GETTER(std::size_t, TypeId, m_objectId.m_typeId);

        //checks if object constructed via reflection on heap or stack.
        GETTER_BOOL(OnHeap, (m_objectId.m_allocatedOn == rtl::alloc::Heap));
        GETTER_BOOL(Empty, (m_object.has_value() == false))

        template<rtl::alloc _allocOn>
        std::pair<error, RObject> clone() const;

        template <class _asType>
        bool canViewAs() const;

        //Returns std::nullopt if type not viewable. Use canViewAs<T>() to check.
        template<class _asType>
        std::optional<view<_asType>> view() const;

        friend detail::RObjectBuilder;
    };


    inline RObject::RObject(std::any&& pObject, std::any&& pWrapper,
                            std::shared_ptr<void>&& pDeleter, const detail::RObjectId& pRObjectId)
        : m_object(std::forward<std::any>(pObject))
        , m_wrapper(std::forward<std::any>(pWrapper))
        , m_deallocator(std::forward<std::shared_ptr<void>>(pDeleter))
        , m_objectId(pRObjectId)
    {
    }


    inline RObject::RObject(RObject&& pOther) noexcept
        : m_object(std::move(pOther.m_object))
        , m_wrapper(std::move(pOther.m_wrapper))
        , m_deallocator(std::move(pOther.m_deallocator))
        , m_objectId(pOther.m_objectId)
    {
        // Explicitly clear moved-from source
        pOther.m_object.reset();
        pOther.m_wrapper.reset();
        pOther.m_deallocator.reset();
        pOther.m_objectId.reset();
    }
}