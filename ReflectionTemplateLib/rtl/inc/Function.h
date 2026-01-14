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

#include <inc/type_meta.h>

namespace rtl 
{
/*  @class: Function, (callable object)
    * every functor (function/method pointer), constructor registered will produce a 'Function' object
    * it contains the meta-data of the functor along with 'FunctorId' to lookup for the same in functor-table.
    * once the Function object is obtained, it can be called with the correct set of arguments, which will finally
    * perform call on the functor represented by this object.
*/  class Function
    {
        //member::Const/Mute represents the const/non-const member-function, Type::None for non-member & static-member functions.
        detail::member m_member_kind;

        //type id of class/struct (if it represents a member-function, else always '0')
        traits::uid_t m_recordTypeId;

        //name of the class/struct it belongs to, empty for non-member function.
        std::string m_recordStr;

        //name of the function as supplied by the user.
        std::string m_function;

        //name of the namespace as supplied by the user.
        std::string m_namespaceStr;

        mutable std::vector<type_meta> m_functorsMeta;

    private:

        Function(const std::string& pNamespace, const std::string& pClassName,
                 const std::string& pFuncName, const type_meta& pFunctorsMeta,
                 const traits::uid_t pRecordTypeId, const detail::member pQualifier);

        void addOverload(const Function& pOtherFunc) const;

    protected:

        bool hasSignatureId(const traits::uid_t pSignatureId) const;

        GETTER_REF_C(std::vector<type_meta>, Functors, m_functorsMeta)

    public:

        //simple inlined getters.
        GETTER(detail::member, MemberKind, m_member_kind);
        GETTER(traits::uid_t, RecordTypeId, m_recordTypeId);

        GETTER_CREF(std::string, RecordName, m_recordStr);
        GETTER_CREF(std::string, Namespace, m_namespaceStr);
        GETTER_CREF(std::string, FunctionName, m_function);
        GETTER_CREF(std::vector<type_meta>, FunctorsMeta, m_functorsMeta)

        Function() = default;
        Function(Function&&) = default;
        Function(const Function&) = default;
        Function& operator=(Function&&) = default;
        Function& operator=(const Function&) = default;

        template<class ...signatureT>
        constexpr const detail::InitFunctionHop<detail::member::None, signatureT...> argsT() const;

        template<class ..._args>
        constexpr bool hasSignature() const;

        friend detail::CxxReflection;
        friend builder::ReflectionBuilder;
    };
}