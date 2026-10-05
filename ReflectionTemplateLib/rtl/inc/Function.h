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

        mutable std::vector<type_meta> m_functorsMeta;

    private:

        Function(const std::string& pRecord, const std::string& pFunction, 
                 const type_meta& pFunctorsMeta, const traits::uid_t pRecordTypeId,
                 const detail::member pQualifier);

        void addOverload(const Function& pOtherFunc) const;

    protected:

        bool hasSignatureId(const traits::uid_t pSignatureId) const;

        constexpr std::vector<type_meta>& getFunctors() const;

    public:

        Function() = default;
        Function(Function&&) = default;
        Function(const Function&) = default;
        Function& operator=(Function&&) = default;
        Function& operator=(const Function&) = default;

        template<class ...signatureT>
        constexpr const detail::InitFunctionHop<detail::member::None, signatureT...> argsT() const;

        template<class ..._args>
        constexpr bool hasSignature() const;

        constexpr const std::string& getRecordName() const;

        constexpr const std::string& getFunctionName() const;

        constexpr const detail::member getMemberKind() const;

        constexpr const traits::uid_t getRecordTypeId() const;

        constexpr const std::vector<type_meta>& getFunctorsMeta() const;

        friend detail::CxxReflection;
        friend builder::ReflectionBuilder;
    };
}


namespace rtl
{
    constexpr std::vector<type_meta>& Function::getFunctors() const {
        return m_functorsMeta;
    }

    constexpr const detail::member Function::getMemberKind() const {
        return m_member_kind;
    };

    constexpr const traits::uid_t Function::getRecordTypeId() const {
        return m_recordTypeId;
    };

    constexpr const std::string& Function::getRecordName() const {
        return m_recordStr;
    };

    constexpr const std::string& Function::getFunctionName() const {
        return m_function;
    };

    constexpr const std::vector<type_meta>& Function::getFunctorsMeta() const {
        return m_functorsMeta;
    }
}