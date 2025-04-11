#include <iostream>
#include "Proxy.hpp"

using namespace proxy_test;

int main() {

    // Call a static method of "Original" dynamically using the Proxy class
    const auto& iret = Proxy::forwardStaticCall("getInstanceCount");
    const auto& icount = std::any_cast<int>(iret);
    std::cout << "proxy static-call, getInstanceCount() return: " << icount << "\n";

    {
        Proxy proxyObj;

        // Call an instance method of "Original" dynamically to get the class name
        const auto& ret0 = proxyObj.forwardCall("getClassName");
        const auto& name = std::any_cast<std::string>(ret0);
        std::cout << "proxy call, getClassName() return: \"" << name << "\"\n";

        // Call an instance method of "Original" dynamically to get the square root of a number
        const auto& ret1 = proxyObj.forwardCall("getSquareRoot", double(10000));
        const auto& sqroot = std::any_cast<double>(ret1);
        std::cout << "proxy call, getSquareRoot() return: " << sqroot << "\n";

        // Call an instance method of "Original" dynamically to set the node name
        proxyObj.forwardCall("setNodeName", std::string("testNode"));
        std::cout << "proxy call, setNodeName() called with string \"testNode\"\n";

        // Call an instance method of "Original" dynamically to get the node name
        const auto& ret2 = proxyObj.forwardCall("getNodeName");
        std::cout << "proxy call, getNodeName() return: \"" << std::any_cast<std::string>(ret2) << "\"\n";
    }

    // Call the static method of "Original" again to get the updated instance count
    const auto& oret = Proxy::forwardStaticCall("getInstanceCount");
    const auto& ocount = std::any_cast<int>(oret);
    std::cout << "proxy static-call, getInstanceCount() return: " << ocount << "\n";

    return 0;
}