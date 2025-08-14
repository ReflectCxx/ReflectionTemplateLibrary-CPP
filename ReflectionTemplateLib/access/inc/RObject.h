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

    class RObjExtractor;

    struct RObjectBuilder;
}


namespace rtl::access
{
    class Function;

    //Reflecting the object within.
    class RObject
    {
        using Cloner = std::function<RObject(error&, const RObject&, rtl::alloc)>;

        mutable Cloner m_getClone;
        mutable std::any m_object;
        mutable detail::RObjectId m_objectId;

        static std::atomic<std::size_t> m_rtlManagedInstancesCount;

        RObject(const RObject&) = default;
        RObject(std::any&& pObject, Cloner&& pCloner, const detail::RObjectId& pRObjectId);

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
    *   - External objects (e.g. returned via Reflected call) keep original qualifier; if const, then const_cast is unsafe.
    */  GETTER_BOOL(ConstCastSafe, m_objectId.m_isConstCastSafe)

        template <class _asType>
        bool canViewAs() const;

        template<rtl::alloc _allocOn>
        std::pair<error, RObject> clone() const;

        template<class T, std::enable_if_t<traits::is_unique_ptr_v<T>, int> = 0>
        std::optional<rtl::view<T>> view() const;

        template<class T, std::enable_if_t<traits::is_shared_ptr_v<T>, int> = 0>
        std::optional<rtl::view<T>> view() const;

        template<class T, std::enable_if_t<traits::is_not_any_wrapper_v<T>, int> = 0>
        std::optional<rtl::view<T>> view() const;

        //friends :)
        template<class T>
        friend struct detail::RObjectUPtr;
        friend detail::RObjExtractor;
        friend detail::RObjectBuilder;
    };
}