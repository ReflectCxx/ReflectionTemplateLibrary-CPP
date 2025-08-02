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
        std::any m_object;
        std::any m_wrapper;
        std::shared_ptr<void> m_deallocator;

        using Cloner = std::function<RObject(error&, const RObject&, rtl::alloc)>;
        Cloner m_getClone;

        detail::RObjectId m_objectId;

        static std::atomic<std::size_t> m_rtlOwnedRObjectInstanceCount;

        RObject(const RObject&) = default;

        RObject(std::any&& pObject, std::any&& pWrapper, std::shared_ptr<void>&& pDeleter, 
                Cloner&& pCopyCtor, const detail::RObjectId& pRObjectId);

        template<class T>
        const T& as(bool pGetFromWrapper = false) const;

        std::size_t getConverterIndex(const std::size_t pToTypeId) const;

        template <class T>
        static std::shared_ptr<void> getDeallocator(T* pObject);

        template <class T>
        static Cloner getCloner();

        template <class T, rtl::alloc _allocOn>
        static RObject create(T&& pVal);

        template <class W>
        static RObject createWithWrapper(W&& pWrapper);

    public:

        RObject() = default;
        ~RObject() = default;
        RObject& operator=(RObject&&) = delete;
        RObject& operator=(const RObject&) = delete;

        RObject(RObject&&) noexcept;

        GETTER(std::any,,m_object)
        GETTER(std::size_t, TypeId, m_objectId.m_typeId)
        GETTER_BOOL(Empty, (m_object.has_value() == false))

        //checks if object constructed via reflection on heap or stack.
        bool isOnHeap() const;

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