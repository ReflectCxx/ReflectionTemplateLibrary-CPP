
#include <iostream>
#include "Proxy.hpp"

using namespace proxy_test;

int main() {

	const auto& iret = Proxy::forwardStaticCall("getInstanceCount");
	const auto& icount = std::any_cast<int>(iret);
	std::cout << "proxy static-call, getInstanceCount() return: " << icount << "\n";

	{
		Proxy proxyObj;

		const auto& ret0 = proxyObj.forwardCall("getClassName");
		const auto& name = std::any_cast<std::string>(ret0);
		std::cout << "proxy call, getClassName() return: \"" << name << "\"\n";
	
		const auto& ret1 = proxyObj.forwardCall("getSquareRoot", double(10000));
		const auto& sqroot = std::any_cast<double>(ret1);
		std::cout << "proxy call, getSquareRoot() return: " << sqroot << "\n";
	
		proxyObj.forwardCall("setNodeName", std::string("testNode"));
		std::cout << "proxy call, setNodeName() called with string \"testNode\"\n";

		const auto& ret2 = proxyObj.forwardCall("getNodeName");
		std::cout << "proxy call, getNodeName() return: \"" << std::any_cast<std::string>(ret2) << "\"\n";
	}

	const auto& oret = Proxy::forwardStaticCall("getInstanceCount");
	const auto& ocount = std::any_cast<int>(oret);
	std::cout << "proxy static-call, getInstanceCount() return: " << ocount << "\n";

	return 0;
}