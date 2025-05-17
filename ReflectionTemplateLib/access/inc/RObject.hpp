#pragma once

#include <RObject.h>

namespace rtl::access {

    template <class T>
    static RObject RObject::create(T&& pVal)
    {
        const auto& typeId = rtl::detail::TypeId<T>::get();
        const auto& typeStr = typeid(T).name();
        return std::move(RObject(pVal, typeId, typeStr));
    }


    template <class _type>
    _type RObject::to() 
    {
        return std::any_cast<_type>(m_val);
    }
}