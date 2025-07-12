#include <iostream>
#include "Proxy.hpp"

using namespace proxy_test;

int main() {

    // Call a static method of "Original" dynamically using the Proxy class
    auto [ierr, irobj] = Proxy::forwardStaticCall("getInstanceCount");
    if (ierr != rtl::error::None || irobj.isEmpty() || !irobj.canReflectAs<unsigned int>()) {
        std::cout << "Proxy call to 'getInstanceCount' failed! (error: " << rtl::to_string(ierr) << ")" << std::endl;
        return -1;
    }

    const auto& icount = irobj.view<unsigned int>()->get();
    std::cout << "proxy static-call, getInstanceCount() return: " << icount << "\n";

    {
        Proxy proxyObj;

        // Call an instance method of "Original" dynamically to get the class name
        auto [err0, robj0] = proxyObj.forwardCall("getClassName");
        if (err0 != rtl::error::None || robj0.isEmpty() || !robj0.canReflectAs<std::string>()) {
            std::cout << "Proxy call to 'getClassName' failed! (error: " << rtl::to_string(err0) << ")" << std::endl;
            return -1;
        }
        const auto& name0 = robj0.view<std::string>()->get();
        std::cout << "proxy call, getClassName() return: \"" << name0 << "\"\n";


        // Call an instance method of "Original" dynamically to get the square root of a number
        auto [err1, robj1] = proxyObj.forwardCall("getSquareRoot", double(10000));
        if (err1 != rtl::error::None || robj1.isEmpty() || !robj1.canReflectAs<double>()) {
            std::cout << "Proxy call to 'getSquareRoot' failed! (error: " << rtl::to_string(err1) << ")" << std::endl;
            return -1;
        }
        const auto& sqroot = robj1.view<double>()->get();
        std::cout << "proxy call, getSquareRoot() return: " << sqroot << "\n";

        // Call an instance method of "Original" dynamically to set the node name
        auto [err2, robj2] = proxyObj.forwardCall("setNodeName", std::string("testNode"));
        if (err2 != rtl::error::None) {
            std::cout << "Proxy call to 'setNodeName' failed! (error: " << rtl::to_string(err2) << ")" << std::endl;
            return -1;
        }
        std::cout << "proxy call, setNodeName() called with string \"testNode\"\n";

        // Call an instance method of "Original" dynamically to get the node name
        auto [err3, robj3] = proxyObj.forwardCall("getNodeName");
        if (err3 != rtl::error::None || robj3.isEmpty() || !robj3.canReflectAs<std::string>()) {
            std::cout << "Proxy call to 'getNodeName' failed! (error: " << rtl::to_string(err3) << ")" << std::endl;
            return -1;
        }
        const auto& name1 = robj3.view<std::string>()->get();
        std::cout << "proxy call, getNodeName() return: \"" << name1 << "\"\n";
    }

    // Call the static method of "Original" again to get the updated instance count
    const auto [oerr, orobj] = Proxy::forwardStaticCall("getInstanceCount");
    if (oerr != rtl::error::None || orobj.isEmpty() || !orobj.canReflectAs<unsigned int>()) {
        std::cout << "Proxy call to 'getInstanceCount' failed! (error: " << rtl::to_string(oerr) << ")" << std::endl;
        return -1;
    }
    const auto& ocount = orobj.view<unsigned int>()->get();
    if (ocount != 0) {
        std::cout << "proxy static-call, getInstanceCount() return: " << ocount << ".\nReflected instance not destroyed, memory leak. FAILURE!!\n";
    }
    else {
        std::cout << "proxy static-call, getInstanceCount() return: " << ocount << "\n";
    }
    return 0;
}