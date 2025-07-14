
#include "Record.h"
#include "Method.h"
#include "Constants.h"
#include "RObject.h"

namespace rtl {

    namespace access
    {
    /*  @method: create
        @param: ...params (any number/type of arguments)
        @return: std::pair<error, RObject>
        * calls the constructor of the calss/struct represented by this 'Record' object.
        * returns the dynamically allocated object of the calss/struct along with the status.
        * only default or any other overloaded constructor is called, except copy (for that check, Record::clone()).
        * if the signature(...params) did not match any registered ctor, error::SignatureMismatch is returned as RStatus.
        * if no constructor found, error::ReflecetdConstructorNotFound is returned as RStatus.
        * in case of reflected call failure, empty 'RObject' will be returned.
        * on success error::None will be returned along with the newly constructed object wrapped under 'RObject' (type erased).
    */  template<alloc _alloc, class ..._ctorArgs>
        inline std::pair<error, RObject> Record::create(_ctorArgs&& ...params) const
        {
            static_assert(_alloc != rtl::alloc::None, "Instance cannot be created with 'rtl::alloc::None' option.");

            const auto& itr = m_methods.find(CtorName::ctor(m_recordName));
            //if registered constructor is found for the class/struct represented by this 'Record' object.
            if (itr != m_methods.end()) {
                //invoke the constructor, forwarding the arguments.
                return itr->second.invokeCtor(_alloc, std::forward<_ctorArgs>(params)...);
            }
            else {
                //if no constructor found, return with empty 'RObject'.
                return { error::ConstructorNotRegisteredInRTL, RObject() };
            }
        }
    }
}