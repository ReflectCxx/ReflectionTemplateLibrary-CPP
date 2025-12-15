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


/*      @method: create
        @param: ...params (any number/type of arguments)
        @return: Return
        * calls the constructor of the calss/struct represented by this 'Record' object.
        * returns the dynamically allocated object of the calss/struct along with the status.
        * only default or any other overloaded constructor is called, except copy (for that check, Record::clone()).
        * if the signature(...params) did not match any registered ctor, error::SignatureMismatch is returned with empty 'RObject'.
        * if no constructor found, error::ConstructorNotRegisteredInRtl is returned with empty 'RObject'.
        * on success error::None and newly constructed object wrapped under 'RObject' (type erased, treated as non-const) is returned.
*/      template<alloc _alloc, class ..._ctorArgs>
        Return create(_ctorArgs&& ...params) const
        {
            static_assert(_alloc != rtl::alloc::None, "Instance cannot be created with 'rtl::alloc::None' option.");
            const auto& method = m_methods.at(detail::ctor_name(m_recordName));
            const detail::FunctorId& clonerId = method.getFunctorIds()[detail::Index::CopyCtor];
            return method.invokeCtor(_alloc, clonerId, std::forward<_ctorArgs>(params)...);
        }

        //only class which can create objects of this class & manipulates 'm_methods'.
        friend class detail::CxxReflection;
    };
}


namespace rtl
{
    template<class ...args_t>
    inline constructor<args_t...> Record::ctor() const
    {
        constructor<args_t...> fnCtor;
        const auto& method = m_methods.at(detail::ctor_name(m_recordName));
        const auto& functorsMeta = method.getFunctorsMeta();

        std::vector<rtl::type_meta> fnTyMetas(detail::call_by::ncref);

        auto normalId = traits::uid<traits::normal_sign_id_t<args_t...>>::value;
        for (auto& ty_meta : functorsMeta)
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

        std::size_t index = rtl::index_none;
        auto strictId = traits::uid<traits::strict_sign_id_t<args_t...>>::value;
        for (int i = 0; i < fnTyMetas.size(); i++)
        {
            auto& ty_meta = fnTyMetas[i];
            if (!ty_meta.is_empty() && ty_meta.get_strict_args_id() == strictId) {
                index = i;
                break;
            }
        }

        return fnCtor;
    }
}