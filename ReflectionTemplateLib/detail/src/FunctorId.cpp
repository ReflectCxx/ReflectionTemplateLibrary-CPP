
#include "FunctorId.h"

namespace rtl
{
    namespace detail
    {
    /*  @method: getHashCode()
        @return: std::size_t (a unique hash-code for a functor)
        * 'm_containerId' will be same for functors(non-member) with same signatures.
        * for member functions, a functor will have three atrributes
            - signature
            - whether it is const or non-const
            - class/struct type
          'm_containerId' will be same for functors with same above attributes.
        * every functor will have a distinct index in the functor-wrapped-lambda-table.
        * so, combination of m_containerId & m_index is unique for every functor.
    */  std::size_t FunctorId::getHashCode() const
        {
            return std::stoull(std::to_string(m_containerId) +
                               std::to_string(m_index) +
                               std::to_string(m_recordId) +
                               std::to_string(m_returnId));
        }
    }
}