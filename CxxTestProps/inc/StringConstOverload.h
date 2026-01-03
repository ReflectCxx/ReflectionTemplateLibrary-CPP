#pragma once

#include <string>

struct StrConstOverload 
{
	constexpr static const char* struct_ = "StrConstOverload";

	std::string reverseString();

	std::string reverseString() const;
};