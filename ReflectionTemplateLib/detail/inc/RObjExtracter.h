#pragma once

#include "RObject.h"

namespace rtl::detail
{
    class RObjExtractor
    {
        friend access::RObject;
        
        const access::RObject& m_rObj;
        
        RObjExtractor(const access::RObject* pRObj) : m_rObj(*pRObj) { }

        template<class T>
        static const T* getPointer(const std::any& pObject, const EntityKind pEntityKind)
        {
            try {
                switch (pEntityKind)
                {
                case detail::EntityKind::Pointer: {
                    return std::any_cast<const T*>(pObject);
                }
                case detail::EntityKind::Value: {
                    const T& valueRef = std::any_cast<const T&>(pObject);
                    return static_cast<const T*>(&valueRef);
                }
                }
            }
            catch (const std::bad_any_cast&) { /*TODO: log the failure. */ }
            return nullptr;
        }


        template<class T>
        const T* getPointer() const
        {
            try {
                switch (m_rObj.m_objectId.m_containsAs)
                {
                    case detail::EntityKind::Pointer: {
                        return std::any_cast<const T*>(m_rObj.m_object);
                    }
                    case detail::EntityKind::Wrapper: {
                        return getFromWrapper<T>();
                    }
                    case detail::EntityKind::Value: {
                        const T& valueRef = std::any_cast<const T&>(m_rObj.m_object);
                        return static_cast<const T*>(&valueRef);
                    }
                }
            }
            catch (const std::bad_any_cast&) { /*TODO: log the failure. */ }
            return nullptr;
        }


        template <class T, traits::enable_if_unique_ptr<T> = 0>
        auto getWrapper() const -> const RObjectUPtr<typename traits::std_wrapper<T>::value_type>*
        {
            try {
                if (m_rObj.m_objectId.m_wrapperType == detail::Wrapper::Unique)
                {
                    using _T = traits::std_wrapper<T>::value_type;
                    if constexpr (traits::is_const_v<_T>)
                    {
                        if (m_rObj.m_objectId.m_isWrappingConst)
                        {
                            using U = detail::RObjectUPtr<const _T>;
                            const U& uptrRef = std::any_cast<const U&>(m_rObj.m_object);
                            return static_cast<const U*>(&uptrRef);
                        }
                    }
                    else
                    {
                        using U = detail::RObjectUPtr<_T>;
                        const U& uptrRef = std::any_cast<const U&>(m_rObj.m_object);
                        return static_cast<const U*>(&uptrRef);
                    }
                }
            }
            catch (const std::bad_any_cast&) { /*TODO: log the failure. */ }
            return nullptr;
        }


        template <class T, traits::enable_if_shared_ptr<T> = 0>
        const T* getWrapper() const
        {
            try {
                if (m_rObj.m_objectId.m_wrapperType == detail::Wrapper::Shared)
                {
                    using _T = traits::std_wrapper<T>::value_type;
                    if constexpr (traits::is_const_v<_T>)
                    {
                        if (m_rObj.m_objectId.m_isWrappingConst) {
                            using U = std::shared_ptr<const _T>;
                            const U& sptrRef = std::any_cast<const U&>(m_rObj.m_object);
                            return static_cast<const T*>(&sptrRef);
                        }
                    }
                    else
                    {
                        using U = std::shared_ptr<_T>;
                        const U& sptrRef = std::any_cast<const U&>(m_rObj.m_object);
                        return static_cast<const T*>(&sptrRef);
                    }
                }
            }
            catch (const std::bad_any_cast&) { /*TODO: log the failure. */ }
            return nullptr;
        }


        template<class T>
        const T* getFromWrapper() const
        {
            try {
                if (m_rObj.m_objectId.m_wrapperType == detail::Wrapper::Unique)
                {
                    if (m_rObj.m_objectId.m_isWrappingConst) {
                        using U = detail::RObjectUPtr<const T>;
                        const U& uptrRef = std::any_cast<const U&>(m_rObj.m_object);
                        return static_cast<const T*>(uptrRef.get());
                    }
                    else {
                        using U = detail::RObjectUPtr<T>;
                        const U& uptrRef = std::any_cast<const U&>(m_rObj.m_object);
                        return static_cast<const T*>(uptrRef.get());
                    }
                }
                if (m_rObj.m_objectId.m_wrapperType == detail::Wrapper::Shared)
                {
                    if (m_rObj.m_objectId.m_isWrappingConst) {
                        using U = std::shared_ptr<const T>;
                        const auto& sptrRef = std::any_cast<const U&>(m_rObj.m_object);
                        return static_cast<const T*>(sptrRef.get());
                    }
                    else {
                        using U = std::shared_ptr<T>;
                        const auto& sptrRef = std::any_cast<const U&>(m_rObj.m_object);
                        return static_cast<const T*>(sptrRef.get());
                    }
                }
            }
            catch (const std::bad_any_cast&) { /*TODO: log the failure. */ }
            return nullptr;
        }
	};
}