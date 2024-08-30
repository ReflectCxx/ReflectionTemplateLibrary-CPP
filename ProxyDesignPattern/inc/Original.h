#pragma once

#include <string>

namespace proxy_test {

	class Original 
	{
	public:

		std::string getClassId();

		const double getSquareRoot(const double pNum);
	};
}