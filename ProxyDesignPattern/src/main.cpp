
#include <iostream>
#include "Proxy.h"

using namespace proxy_test;

int main() {

	Proxy proxyObj;

	const auto& ret = proxyObj.forwardCall("getClassId");
	const auto& classId = std::any_cast<std::string>(ret);
	std::cout << "\nproxy call, getClassId() return: " << classId << "\n";

	const auto& ret1 = proxyObj.forwardCall("getSquareRoot", double(10000));
	const auto& sqroot = std::any_cast<double>(ret1);
	std::cout << "\nproxy call, getSquareRoot() return: " << sqroot << "\n";

	return 0;
}