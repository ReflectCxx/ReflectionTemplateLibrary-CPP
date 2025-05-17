#pragma once

#include <any>
#include <string>
#include <optional>
#include <functional>

#include "Constants.h"

namespace rtl::access 
{
    class RObject
    {
        std::any m_object;
        std::size_t m_typeId;
        std::string m_typeStr;
        alloc m_allocatedOn;

        RObject() = default;

        RObject(std::any pObjRef, std::size_t pTypeId, std::string pTypeStr, alloc pAllocOn);

        // Throws: std::bad_any_cast if the contained type does not match T
        template <class T>
        T& as();

        template <class T>
        const bool isa();

    public:

        ~RObject() = default;

        //Copy not allowed.
        RObject(const RObject&) = delete;
        RObject& operator=(const RObject&) = delete;

        //Only move allowed.
        RObject(RObject&& pOther) noexcept;
        RObject& operator=(RObject&& pOther) noexcept;

        GETTER(std::string, TypeStr, m_typeStr)

        template <class T>
        std::optional<std::reference_wrapper<T>> ref() noexcept;

        template <alloc _allocOn, class T>
        static RObject create(T&& pVal);

    };
}