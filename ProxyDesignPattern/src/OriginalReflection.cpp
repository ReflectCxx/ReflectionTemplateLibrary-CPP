#include "OriginalReflection.h"
#include "Original.h"

using namespace rtl::builder;
using namespace rtl::access;

namespace proxy_test
{
    /**
     * @brief Constructs an OriginalReflection object and registers the "Original" class and its methods for reflection.
     *
     * This constructor initializes the CxxMirror base class with reflection records for the "Original" class,
     * including its constructor, instance methods, and static methods. It also initializes the reflectedClass
     * member with the reflection data for the "Original" class.
     */
    OriginalReflection::OriginalReflection() :CxxMirror(
        {
            Reflect().record<Original>("Original").constructor().build(),
            Reflect().record<Original>("Original").method("getClassName").build(&Original::getClassName),
            Reflect().record<Original>("Original").method("getSquareRoot").build(&Original::getSquareRoot),
            Reflect().record<Original>("Original").method("setNodeName").build(&Original::setNodeName),
            Reflect().record<Original>("Original").method("getNodeName").build(&Original::getNodeName),
            Reflect().record<Original>("Original").methodStatic("getInstanceCount").build(&Original::getInstanceCount)
        })
    {
        reflectedClass = getRecord("Original");
    }
}
