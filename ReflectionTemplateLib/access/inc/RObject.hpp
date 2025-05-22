#pragma once

#include <optional>

#include "RObject.h"
#include "RObjectConverters.h"

namespace rtl::access {

    template<class T>
    inline const T& RObject::as() const
    {
        return std::any_cast<const T&>(m_object);
    }


    template<class T>
    inline const bool RObject::isReflecting() const
    {
        const auto& typeId = rtl::detail::TypeId<T>::get();
        return (typeId == m_typeId || getConverterIndex(typeId) != -1);
    }


    template <alloc _allocOn, class T>
    inline RObject RObject::create(T&& pVal)
    {
        using _type = remove_const_and_reference<T>;
        const auto& typeId = rtl::detail::TypeId<_type>::get();
        const auto& typeStr = rtl::detail::TypeId<_type>::toString();
        const auto& conversions = rtl::detail::RObjectConverter<_type>::getConversions();
        return RObject(std::any(std::forward<T>(pVal)), typeId, typeStr, _allocOn, conversions);
    }


    template <alloc _allocOn, class T>
    inline RObject RObject::reflect(T&& pVal)
    {
        if constexpr (is_string_like<std::decay_t<T>>::value) {
            return create<_allocOn>(std::string(pVal));
        }
        else {
            return create<_allocOn>(pVal);
        }
    }


    template<class _asType>
    inline const std::size_t RObject::getTypeId() const
    {
        if constexpr (std::is_same_v<_asType, char>) 
        {
            // Special case: char → const char* view if underlying type is std::string
            if (m_typeId == rtl::detail::TypeId<std::string>::get()) {
                return rtl::detail::TypeId<const char*>::get();
            }
            else {
                return rtl::detail::TypeId<_asType>::get();
            }
        }
        else {
            return rtl::detail::TypeId<_asType>::get();
        }
    }


    template <class _asConstPtrT, std::enable_if_t<std::is_pointer_v<_asConstPtrT>, int>>
    inline _asConstPtrT RObject::view() const
    {
        //using _asConstT = std::remove_pointer_t<_asConstPtrT>;
        //using _asT = std::remove_const_t<_asConstT>;

        //const auto& toTypeId = rtl::detail::TypeId<_asT>::get();

        //if (toTypeId == m_typeId) {
        //    // Only allow const pointer types
        //    static_assert(std::is_const_v<RawType>,
        //        "Cannot get non-const pointer from const RObject. Use view<const T*>() instead.");
        //    return static_cast<_asConstPtrT>(&as<RawType>());
        //}
        //return nullptr;

        ////using _rawType = std::remove_cv_t<std::remove_pointer_t<_asType>>;
        //
        ////const auto& rawTypeId = rtl::detail::TypeId<_rawType>::get();
        //const auto& toTypeId = rtl::detail::TypeId<_asType>::get();

        //if (toTypeId == m_typeId) {
        //    return static_cast<const _asType>(&as<std::remove_pointer_t<_asType>>());
        //}

        ////const auto& index = getConverterIndex(toTypeId);
        ////if (index != -1) {
        ////    const auto& converted = m_converters[index].second(m_object);
        ////    const _asType* viewPtr = std::any_cast<const _asType*>(converted);
        ////    return viewPtr;
        ////}
        //return nullptr;
    }
}