
#include "OriginalReflection.h"
#include "Original.h"

using namespace rtl::builder;
using namespace rtl;

namespace proxy_test
{
    /**
     * @brief Retrieves the reflection data for the "Original" class.
     *
     * This method uses the CxxMirror reflection system to dynamically register the "Original" class,
     * including its constructor, instance methods, and static methods. The reflection data is stored
     * as a static optional object to ensure it is initialized only once and reused across multiple calls.
     *
     * @return const std::optional<rtl::Record>& A reference to the optional reflection data
     * for the "Original" class. If the reflection data is unavailable, the optional will be empty.
     */
    const std::optional<rtl::Record>& OriginalReflection::getClass()
    {
        // Static reflection data for the "Original" class
        static std::optional<rtl::Record> reflectedClass = CxxMirror<0>::reflect(
            {
                // Register the default constructor of the "Original" class
                type().nameSpace().record<Original>("Original").build(),

                // Register the instance method: getClassName
                type().member<Original>().method("getClassName").build(&Original::getClassName),

                // Register the instance method: getSquareRoot
                type().member<Original>().method("getSquareRoot").build(&Original::getSquareRoot),

                // Register the instance method: setNodeName
                type().member<Original>().method("setNodeName").build(&Original::setNodeName),

                // Register the instance method: getNodeName
                type().member<Original>().method("getNodeName").build(&Original::getNodeName),

                // Register the static method: getInstanceCount
                type().member<Original>().methodStatic("getInstanceCount").build(&Original::getInstanceCount)

            }).getRecord("Original");

        // Return the reflection data for the "Original" class
        return reflectedClass;
    }
}