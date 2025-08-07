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
}

namespace rtl::access
{
    class Function;

    //Reflecting the object within.
    class RObject
    {
        using Deleter = std::function<void()>;
        using Cloner = std::function<RObject(error&, const RObject&, rtl::alloc)>;
        
        std::any m_object;
        std::any m_wrapper;
        Cloner m_getClone;
        Deleter m_deleter;
        detail::RObjectId m_objectId;

        static std::atomic<std::size_t> m_rtlOwnedHeapAllocCount;

        RObject(const RObject&) = default;
        RObject(std::any&& pObject, std::any&& pWrapper, Deleter&& pDeleter, 
                Cloner&& pCopyCtor, const detail::RObjectId& pRObjectId);

        template<class T>
        const T& as(bool pGetFromWrapper = false) const;

        std::size_t getConverterIndex(const std::size_t pToTypeId) const;

        template <rtl::alloc _allocOn>
        std::pair<error, RObject> createCopy() const;

        template <class T>
        static Cloner getCloner();

        template <class T, rtl::alloc _allocOn>
        static RObject create(T&& pVal);

        template <class W>
        static RObject createWithWrapper(W&& pWrapper);

    public:

        ~RObject();
        RObject() = default;
        RObject(RObject&&) noexcept;
        RObject& operator=(RObject&&) = delete;
        RObject& operator=(const RObject&) = delete;

        GETTER(std::any,,m_object)
        GETTER(std::size_t, TypeId, m_objectId.m_typeId)
        GETTER_BOOL(Empty, (m_object.has_value() == false))
        GETTER_BOOL(OnHeap, (m_objectId.m_allocatedOn == alloc::Heap))
        GETTER_BOOL(RefOrPtr, (m_objectId.m_isPointer == IsPointer::Yes))
        // Objects created through reflection are considered mutable (non-const) by default.
        GETTER_BOOL(Const, m_objectId.m_isTypeConst)

        template<rtl::alloc _allocOn>
        std::pair<error, RObject> clone() const;

        template <class _asType>
        bool canViewAs() const;

        //Returns std::nullopt if type not viewable. Use canViewAs<T>() to check.
        template<class _asType>
        std::optional<view<_asType>> view() const;

        friend detail::RObjectBuilder;
    };
}