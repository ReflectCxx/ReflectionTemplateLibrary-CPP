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
    template<class  T>
    struct RObjectUPtr;
    struct RObjectBuilder;
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
        
        std::size_t getConverterIndex(const std::size_t pToTypeId) const;

        template <class T, traits::enable_if_unique_ptr<T> = 0>
        T extractWrapper() const;

        template <class T, traits::enable_if_shared_ptr<T> = 0>
        const T* extractWrapper() const;

        template<class T>
        const T* extractRefrence() const;

        template<class T>
        const T* extractFromWrapper() const;

        template<class T>
        std::optional<rtl::view<T>> performConversion(const std::size_t pIndex) const;

    public:

        RObject() = default;
        ~RObject() = default;
        RObject(RObject&&) noexcept;
        RObject& operator=(RObject&&) = delete;
        RObject& operator=(const RObject&) = delete;

        GETTER(std::size_t, TypeId, m_objectId.m_typeId)
        GETTER_BOOL(Empty, (m_object.has_value() == false))
        GETTER_BOOL(OnHeap, (m_objectId.m_allocatedOn == alloc::Heap))

    /*  Reflection Const Semantics:
    *   - All reflected objects default to mutable internally; API enforces logical constness.
    *   - RTL may 'const_cast' its own objects(allocated via RTL) but preserves logical constness.
    *   - External objects (e.g. returned via Reflected call ) keep original const; const_cast is unsafe.
    */  GETTER_BOOL(ConstCastSafe, m_objectId.m_isConstCastSafe)

        template <class _asType>
        bool canViewAs() const;

        template<rtl::alloc _allocOn>
        std::pair<error, RObject> clone() const;

        template<class T, traits::enable_if_std_wrapper<T> = 0>
        std::optional<rtl::view<T>> view() const;

        template<class T, traits::enable_if_not_std_wrapper<T> = 0>
        std::optional<rtl::view<T>> view() const;

        //friends :)
        template<class T>
        friend struct detail::RObjectUPtr;
        friend detail::RObjectBuilder;
    };
}