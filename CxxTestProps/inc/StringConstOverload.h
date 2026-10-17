#pragma once

#include <string>

struct StrConstOverload 
{
	constexpr static std::string_view struct_ = "StrConstOverload";

	std::string reverseString();

	std::string reverseString() const;
};