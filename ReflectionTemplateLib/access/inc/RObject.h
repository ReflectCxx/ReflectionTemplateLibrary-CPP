#pragma once

#include <any>
#include <string>


namespace rtl::access 
{
    class RObject
    {
        const std::any m_object;
        const std::size_t m_typeId;
        const std::string m_typeStr;

    public:

        explicit RObject(std::any&& pObjRef, std::size_t&& pTypeId, std::string&& pTypeStr);

        template <class T>
        static RObject create(T&& pVal);

        template <class _type>
        _type to();
    };
}