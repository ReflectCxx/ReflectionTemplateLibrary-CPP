#pragma once

#include <string>
#include <vector>
#include <functional>

#include "RStatus.h"
#include "FunctorId.h"
#include "Constants.h"

namespace rtl {

    namespace detail {
		//forward decls
        class CxxReflection;
		class ReflectionBuilder;
	}

    namespace access
	{
    /*  @class: Function, (callable object)
        * every functor (function/method pointer), constructor, destructor registered will produce a 'Function' object
        * it contains the meta-data of the functor along with 'FunctorId' to lookup for the same in functor-table.
        * once the Function object is obtained, it can be called with the correct set of arguments, which will finally 
          perform call on the functor represented by this object.
    */  class Function
        {
            //TypeQ::Const/Mute represents the const/non-const member-function, Type::None for non-member functions.
            const TypeQ m_qualifier;

            //type id of class/struct (if it represents a member-function, else always '0')
            const std::size_t m_recordTypeId;

            //name of the class/struct it belongs to, empty for non-member function.
            const std::string m_record;

            //name of the function as supplied by the user.
            const std::string m_function;

            //name of the namespace as supplied by the user.
            const std::string m_namespace;

            //FunctorId acts as a hash-key to look up the functor in table. multiple 'FunctoreId' for overloaded functors.
            mutable std::vector<detail::FunctorId> m_functorIds;

            Function(const std::string& pNamespace, const std::string& pClassName, 
                     const std::string& pFuncName, const detail::FunctorId& pFunctorId,
                     const std::size_t pRecordTypeId, const TypeQ pQualifier);

            void addOverload(const Function& pOtherFunc) const;

            GETTER_REF(std::vector<detail::FunctorId>, FunctorIds, m_functorIds)

        protected:

            Function(const Function& pOther, const detail::FunctorId& pFunctorId,
                     const std::string& pFunctorName);

            const std::size_t hasSignatureId(const std::size_t& pSignatureId) const;

        public:

            //simple inlined getters.
            GETTER(TypeQ, Qualifier, m_qualifier)
            GETTER(std::string, RecordName, m_record)
            GETTER(std::string, Namespace, m_namespace)
            GETTER(std::string, FunctionName, m_function)
            GETTER(std::size_t, RecordTypeId, m_recordTypeId)
            GETTER(std::vector<detail::FunctorId>, Functors, m_functorIds)

            //indicates if a functor associated with it takes zero arguments.
            const bool hasSignature() const;

            template<class ..._args>
            const bool hasSignature() const;

            template<class ..._args>
            RStatus operator()(_args...params) const noexcept;

            template<class ..._args>
            RStatus call(_args...params) const noexcept;

            friend detail::CxxReflection;
            friend detail::ReflectionBuilder;
        };
    }
}