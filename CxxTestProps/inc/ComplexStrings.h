#pragma once

#include <string>

std::string getComplexNumAsString();

std::string reverseString();

std::string reverseString(const char* pStr);

std::string reverseString(std::string pStr);              // (1) by value

std::string reverseString(std::string& pStr);             // (2) lvalue ref

std::string reverseString(const std::string& pStr);       // (3) const lvalue ref

std::string reverseString(std::string&& pStr);            // (4) rvalue ref

std::string reverseString(std::string* pStr);			  // (5) pointer

std::string reverseString(const std::string* pStr);		  // (6) pointer to const

std::string reverseString(const std::string_view& pStr);


namespace complex
{
	double getMagnitude();

	void setReal(double pNum);

	void setImaginary(double pNum);
}