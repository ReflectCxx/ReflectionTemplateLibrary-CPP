/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                         *
 *                                                                       *
 *************************************************************************/


#pragma once

#include "RObject.h"

namespace rtl::detail
{
    class RObjExtractor
    {
        friend RObject;
        
        const RObject& m_rObj;
        
        RObjExtractor(const RObject* pRObj) : m_rObj(*pRObj) { }

        template<class T>
        FORCE_INLINE static const T* getPointer(const std::any& pObject, const EntityKind pEntityKind)
        {
            switch (pEntityKind)
            {
                case EntityKind::Ref: {
                    return std::any_cast<const T*>(pObject);
                }
                case EntityKind::Value: {
                    const T& valueRef = std::any_cast<const T&>(pObject);
                    return static_cast<const T*>(&valueRef);
                }
                default: return nullptr;
            }
            return nullptr;
        }


        template<class T>
        FORCE_INLINE const T* getPointer() const
        {
            switch (m_rObj.m_objectId.m_containsAs)
            {
                case EntityKind::Ref: {
                    return std::any_cast<const T*>(m_rObj.m_object.value());
                }
                case EntityKind::Wrapper: {
                    return getFromWrapper<T>();
                }
                case EntityKind::Value: {
                    const T& valueRef = std::any_cast<const T&>(m_rObj.m_object.value());
                    return static_cast<const T*>(&valueRef);
                }
                default: return nullptr;
            }
            return nullptr;
        }


        template <class T, traits::enable_if_unique_ptr<T> = 0>
        FORCE_INLINE auto getWrapper() const -> const RObjectUPtr<typename traits::std_wrapper<T>::value_type>*
        {
            if (m_rObj.m_objectId.m_wrapperType == detail::Wrapper::Unique)
            {
                using _T = traits::std_wrapper<T>::value_type;
                if constexpr (traits::is_const_v<_T>)
                {
                    if (m_rObj.m_objectId.m_isWrappingConst)
                    {
                        using U = detail::RObjectUPtr<const _T>;
                        const U& uptrRef = std::any_cast<const U&>(m_rObj.m_object.value());
                        return static_cast<const U*>(&uptrRef);
                    }
                }
                else
                {
                    using U = detail::RObjectUPtr<_T>;
                    const U& uptrRef = std::any_cast<const U&>(m_rObj.m_object.value());
                    return static_cast<const U*>(&uptrRef);
                }
            }
            return nullptr;
        }


        template <class T, traits::enable_if_shared_ptr<T> = 0>
        FORCE_INLINE const T* getWrapper() const
        {
            if (m_rObj.m_objectId.m_wrapperType == detail::Wrapper::Shared)
            {
                using _T = traits::std_wrapper<T>::value_type;
                if constexpr (traits::is_const_v<_T>)
                {
                    if (m_rObj.m_objectId.m_isWrappingConst) {
                        using U = std::shared_ptr<const _T>;
                        const U& sptrRef = std::any_cast<const U&>(m_rObj.m_object.value());
                        return static_cast<const T*>(&sptrRef);
                    }
                }
                else
                {
                    using U = std::shared_ptr<_T>;
                    const U& sptrRef = std::any_cast<const U&>(m_rObj.m_object.value());
                    return static_cast<const T*>(&sptrRef);
                }
            }
            return nullptr;
        }


        template<class T>
        FORCE_INLINE const T* getFromWrapper() const
        {
            if constexpr (std::is_destructible_v<T>)
            {
                if (m_rObj.m_objectId.m_wrapperType == detail::Wrapper::Unique)
                {
                    if (m_rObj.m_objectId.m_isWrappingConst) {
                        using U = detail::RObjectUPtr<const T>;
                        const U& uptrRef = std::any_cast<const U&>(m_rObj.m_object.value());
                        return static_cast<const T*>(uptrRef.get());
                    }
                    else {
                        using U = detail::RObjectUPtr<T>;
                        const U& uptrRef = std::any_cast<const U&>(m_rObj.m_object.value());
                        return static_cast<const T*>(uptrRef.get());
                    }
                }
                if (m_rObj.m_objectId.m_wrapperType == detail::Wrapper::Shared)
                {
                    if (m_rObj.m_objectId.m_isWrappingConst) {
                        using U = std::shared_ptr<const T>;
                        const auto& sptrRef = std::any_cast<const U&>(m_rObj.m_object.value());
                        return static_cast<const T*>(sptrRef.get());
                    }
                    else {
                        using U = std::shared_ptr<T>;
                        const auto& sptrRef = std::any_cast<const U&>(m_rObj.m_object.value());
                        return static_cast<const T*>(sptrRef.get());
                    }
                }
            }
            return nullptr;
        }
	};
}