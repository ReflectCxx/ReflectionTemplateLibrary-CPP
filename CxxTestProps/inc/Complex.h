#pragma once

#include <string>

// C-style/free-functions.
std::string getComplexNumAsString();

namespace complex
{
	double getMagnitude();

	void setReal(double pNum);

	void setImaginary(double pNum);
}