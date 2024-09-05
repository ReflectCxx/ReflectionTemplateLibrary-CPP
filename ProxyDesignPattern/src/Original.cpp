
#include <cmath>
#include "Original.h"

namespace proxy_test {

	std::string Original::getClassId()
	{
		return "original";
	}

	const double Original::getSquareRoot(const double pNum)
	{
		return std::sqrt(pNum);
	}
}