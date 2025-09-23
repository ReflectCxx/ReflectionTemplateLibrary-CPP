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

#include <string>
#include <vector>
#include <functional>

#include "FunctorId.h"
#include "rtl_constants.h"
#include "FunctionCaller.h"
#include "lambda_function.h"

namespace rtl {

    namespace detail {
        //forward decls
        class CxxReflection;
        class ReflectionBuilder;
    }

/*  @class: Function, (callable object)
    * every functor (function/method pointer), constructor registered will produce a 'Function' object
    * it contains the meta-data of the functor along with 'FunctorId' to lookup for the same in functor-table.
    * once the Function object is obtained, it can be called with the correct set of arguments, which will finally
    * perform call on the functor represented by this object.
*/  class Function
    {
        //methodQ::Const/Mute represents the const/non-const member-function, Type::None for non-member & static-member functions.
        detail::methodQ m_qualifier;

        //type id of class/struct (if it represents a member-function, else always '0')
        std::size_t m_recordTypeId;

        //name of the class/struct it belongs to, empty for non-member function.
        std::string m_record;

        //name of the function as supplied by the user.
        std::string m_function;

        //name of the namespace as supplied by the user.
        std::string m_namespace;

        //FunctorId acts as a hash-key to look up the functor in table. multiple 'FunctoreId' for overloaded functors.
        mutable std::vector<detail::FunctorId> m_functorIds;

    private:

        Function(const std::string_view pNamespace, const std::string_view pClassName,
                 const std::string_view pFuncName, const detail::FunctorId& pFunctorId,
                 const std::size_t pRecordTypeId, const detail::methodQ pQualifier);

        void addOverload(const Function& pOtherFunc) const;

    protected:

        Function(const Function& pOther, const detail::FunctorId& pFunctorId,
                 const std::string_view pFunctorName);

        const std::size_t hasSignatureId(const std::size_t pSignatureId) const;

        const detail::FunctorId* hasFunctorId(const std::size_t pSignatureId) const;

        GETTER(detail::methodQ, Qualifier, m_qualifier);

        GETTER_REF(std::vector<detail::FunctorId>, FunctorIds, m_functorIds)

    public:

        //simple inlined getters.
        GETTER(std::string, RecordName, m_record);
        GETTER(std::string, Namespace, m_namespace);
        GETTER(std::string, FunctionName, m_function);
        GETTER(std::size_t, RecordTypeId, m_recordTypeId);
        GETTER(std::vector<detail::FunctorId>, Functors, m_functorIds);

        Function() = default;
        Function(Function&&) = default;
        Function(const Function&) = default;
        Function& operator=(Function&&) = default;
        Function& operator=(const Function&) = default;

        detail::Hopper<> lambda();

        bool hasSignature() const;

        template<class ..._args>
        bool hasSignature() const;

        template<class ..._args>
        Return operator()(_args&&...params) const noexcept;

        template<class ..._signature>
        const detail::FunctionCaller<_signature...> bind() const noexcept;

        friend detail::CxxReflection;
        friend detail::ReflectionBuilder;

        template<class ..._signature>
        friend class detail::FunctionCaller;
    };
}