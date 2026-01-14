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

namespace rtl::detail
{
    struct RObjExtractor
    {
        friend RObject;
        
        const RObject* m_rObj;
        
        template<class T>
        ForceInline static const T* getPointer(const std::any& pObject, const EntityKind pEntityKind) noexcept
        {
            switch (pEntityKind)
            {
                case EntityKind::Ptr: {
                    return *(std::any_cast<const T*>(&pObject));
                }
                case EntityKind::Value: {
                    return std::any_cast<const T>(&pObject);
                }
                default: return nullptr;
            }
            return nullptr;
        }


        template<class T>
        ForceInline const T* getPointer() const noexcept
        {
            switch (m_rObj->m_objectId.m_containsAs)
            {
                case EntityKind::Ptr: {
                    return *(std::any_cast<const T*>(&(m_rObj->m_object.value())));
                }
                case EntityKind::Wrapper: {
                    return getFromWrapper<T>();
                }
                case EntityKind::Value: {
                    return std::any_cast<const T>(&(m_rObj->m_object.value()));
                }
                default: return nullptr;
            }
            return nullptr;
        }


        template <class T, traits::enable_if_unique_ptr<T> = 0>
        ForceInline auto getWrapper() const noexcept -> const RObjectUPtr<typename traits::std_wrapper<T>::value_type>*
        {
            if (m_rObj->m_objectId.m_wrapperType == detail::Wrapper::Unique)
            {
                using _T = traits::std_wrapper<T>::value_type;
                if constexpr (traits::is_const_v<_T>)
                {
                    if (m_rObj->m_objectId.m_isWrappingConst)
                    {
                        using U = detail::RObjectUPtr<const _T>;
                        return std::any_cast<const U>(&(m_rObj->m_object.value()));
                    }
                }
                else
                {
                    using U = detail::RObjectUPtr<_T>;
                    return std::any_cast<const U>(&(m_rObj->m_object.value()));
                }
            }
            return nullptr;
        }


        template <class T, traits::enable_if_shared_ptr<T> = 0>
        ForceInline const T* getWrapper() const noexcept
        {
            if (m_rObj->m_objectId.m_wrapperType == detail::Wrapper::Shared)
            {
                using _T = traits::std_wrapper<T>::value_type;
                if constexpr (traits::is_const_v<_T>)
                {
                    if (m_rObj->m_objectId.m_isWrappingConst) {
                        using U = std::shared_ptr<const _T>;
                        return std::any_cast<const U>(&(m_rObj->m_object.value()));
                    }
                }
                else
                {
                    using U = std::shared_ptr<_T>;
                    return std::any_cast<const U>(&(m_rObj->m_object.value()));
                }
            }
            return nullptr;
        }


        template<class T>
        ForceInline const T* getFromWrapper() const noexcept
        {
            if constexpr (std::is_destructible_v<T>)
            {
                if (m_rObj->m_objectId.m_wrapperType == detail::Wrapper::Unique)
                {
                    if (m_rObj->m_objectId.m_isWrappingConst) {
                        using U = detail::RObjectUPtr<const T>;
                        const U* uptr = std::any_cast<const U>(&(m_rObj->m_object.value()));
                        if (uptr != nullptr) {
                            return uptr->get();
                        }
                    }
                    else {
                        using U = detail::RObjectUPtr<T>;
                        const U* uptr = std::any_cast<const U>(&(m_rObj->m_object.value()));
                        if (uptr != nullptr) {
                            return uptr->get();
                        }
                    }
                }
                if (m_rObj->m_objectId.m_wrapperType == detail::Wrapper::Shared)
                {
                    if (m_rObj->m_objectId.m_isWrappingConst) {
                        using U = std::shared_ptr<const T>;
                        const U* sptr = std::any_cast<const U>(&(m_rObj->m_object.value()));
                        if (sptr != nullptr) {
                            return sptr->get();
                        }
                    }
                    else {
                        using U = std::shared_ptr<T>;
                        const U* sptr = std::any_cast<const U>(&(m_rObj->m_object.value()));
                        if (sptr != nullptr) {
                            return sptr->get();
                        }
                    }
                }
            }
            return nullptr;
        }
	};
}