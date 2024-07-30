
#include "Record.h"
#include "RStatus.h"
#include "Method.h"
#include "Constants.h"
#include "Instance.h"

namespace rtl {

    namespace access
    {
    /*  @method: instance
        @param: ...params (any number/type of arguments)
        @return: std::pair<RStatus, Instance>
        * calls the constructor of the calss/struct represented by this 'Record' object.
        * returns the dynamically allocated object of the calss/struct along with the status.
        * only default or any other overloaded constructor is called, except copy (for that check, Record::clone()).
        * if the signature(...params) did not match any registered ctor, Error::SignatureMismatch is returned as RStatus.
        * if no constructor found, Error::ConstructorNotFound is returned as RStatus.
        * in case of reflected call failure, empty 'Instance' will be returned.
        * on success Error::None will be returned along with the newly constructed object wrapped under 'Instance' (type erased).
    */  template<class ..._ctorArgs>
        inline const std::pair<RStatus, Instance> Record::instance(_ctorArgs ...params) const
        {
            const auto& itr = m_methods.find(CtorName::ctor(m_recordName));

            //if registered constructor is found for the class/struct represented by this 'Record' object.
            if (itr != m_methods.end()) {

                //invoke the constructor, forwarding the arguments.
                const RStatus& status = itr->second.invokeCtor(params...);

                //if status is 'true', object construction is successful.
                if (status) {

                    //get the destructor 'Function', which is gauranteed to be present, if at least one constructor is registered.
                    const Function dctor = *getMethod(CtorName::dctor(m_recordName));

                    //construct the 'Instance' object, assigning the destructor as custom deleter, its lifetime is managed via std::shared_ptr.
                    return std::make_pair(status, Instance(status.getReturn(), status, dctor));
                }
                //if reflected call fails, return with empty 'Instance'.
                return std::make_pair(status, Instance());
            }
            else {

                //if no constructor found, return with empty 'Instance'.
                return std::make_pair(RStatus(Error::ConstructorNotFound), Instance());
            }
        }
    }
}