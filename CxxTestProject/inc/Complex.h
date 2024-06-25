#pragma once

#include <string>

std::string getComplexNumAsString();

std::string reverseString();

std::string reverseString(std::string pStr);

std::string reverseString(const char* pStr);

namespace complex
{
	double getMagnitude();

	void setReal(double pNum);

	void setImaginary(double pNum);
}

