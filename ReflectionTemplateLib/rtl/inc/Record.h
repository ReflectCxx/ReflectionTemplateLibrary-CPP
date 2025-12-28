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

#include <memory>
#include <optional>
#include <unordered_map>

#include "Method.h"
#include "function_ptr.h"
#include "rtl_constructor.h"

namespace rtl::detail 
{
    //forward decl.
    class CxxReflection;
}

namespace rtl {

    //forward decls
    class Method;
    class RObject;

/*  @class: Record
    * represents a reflected class/struct.
    * contains registered member-functions as 'Method' objects.
    * provides interface to access methods by name.
    * provides interface to construct instances of the class/struct using the registered constructors.
*/  class Record
    {
        using MethodMap = std::unordered_map< std::string, Method >;

        mutable std::size_t m_recordId;
        mutable std::string m_namespace;
        mutable std::string m_recordName;
        mutable MethodMap m_methods;

    private:

        Record(const std::string& pRecordName, const std::size_t pRecordId, const std::string& pNamespace)
            : m_recordId(pRecordId)
            , m_namespace(pNamespace)
            , m_recordName(pRecordName)
        { }

        GETTER_REF_C(MethodMap, FunctionsMap, m_methods)

    public:

        Record() = delete;
        Record(Record&&) = default;
        Record(const Record&) = default;
        Record& operator=(Record&&) = default;
        Record& operator=(const Record&) = default;

        GETTER_CREF(MethodMap, MethodMap, m_methods)
        GETTER_CREF(std::string, RecordName, m_recordName)
        
        template<class ...args_t>
        constructor<args_t...> ctor() const;

/*      @method: getMethod
        @param: const std::string& (name of the method)
        @return: std::optional<Method>
        * if the method isn't found by the given name, std::nullopt is returned.
*/      std::optional<Method> getMethod(const std::string& pMethod) const
        {
            const auto& itr = m_methods.find(pMethod);
            if (itr != m_methods.end()) {
                return std::optional(itr->second);
            }
            return std::nullopt;
        }

        //only class which can create objects of this class & manipulates 'm_methods'.
        friend class detail::CxxReflection;
    };
}


namespace rtl
{
    template<>
    inline constructor<> Record::ctor() const
    {
        constructor<> fnCtor;
        auto strictId = traits::uid<traits::strict_sign_id_t<alloc>>::value;
        const auto& method = m_methods.at(detail::ctor_name(m_recordName));

        for (auto& ty_meta : method.getFunctorsMeta())
        {
            if (strictId == ty_meta.get_strict_args_id()) 
            {
                using ctor_t = dispatch::function_ptr<Return, alloc>;
                auto fptr = static_cast<const ctor_t&>(ty_meta.get_functor()).f_ptr();
                fnCtor.get_hop().push_back(fptr);
                fnCtor.get_overloads().push_back(&ty_meta.get_functor());
                fnCtor.set_init_error(error::None);
                break;
            }
        }
        return fnCtor;
    }


    template<class ...args_t>
    inline constructor<args_t...> Record::ctor() const
    {
        std::vector<rtl::type_meta> fnTyMetas(detail::call_by::ncref);
        auto normalId = traits::uid<traits::normal_sign_id_t<args_t...>>::value;
        const auto& method = m_methods.at(detail::ctor_name(m_recordName));

        for (auto& ty_meta : method.getFunctorsMeta())
        {
            if (normalId == ty_meta.get_normal_args_id())
            {
                if (normalId == ty_meta.get_strict_args_id()) {
                    fnTyMetas[detail::call_by::value] = ty_meta;
                }
                else if (!ty_meta.is_any_arg_ncref()) {
                    fnTyMetas[detail::call_by::cref] = ty_meta;
                }
                else fnTyMetas.push_back(ty_meta);
            }
        }

        constructor<args_t...> fnCtor;
        for (auto& ty_meta : fnTyMetas)
        {
            if (ty_meta.is_empty()) {
                fnCtor.get_hop().push_back(nullptr);
                fnCtor.get_overloads().push_back(nullptr);
                continue;
            }

            using fn_cast = dispatch::functor_cast<traits::normal_sign_t<args_t>...>;
            auto fn = fn_cast(ty_meta.get_functor()).template to_function<dispatch::erase::t_ctor>();

            fnCtor.get_hop().push_back(fn.f_ptr());
            fnCtor.get_overloads().push_back(&ty_meta.get_functor());
            fnCtor.set_init_error(error::None);
        }

        if (fnCtor.get_init_error() != error::None) {
            fnCtor.set_init_error(error::SignatureMismatch);
        }
        return fnCtor;
    }
}