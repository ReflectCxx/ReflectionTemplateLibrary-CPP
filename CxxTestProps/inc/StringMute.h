#pragma once

#include <string>

// 'StrMute' - String-Mutable, all methods are non-const.
struct StrMute
{
	constexpr static const char* struct_ = "StrMute";

	std::string reverseString();

	std::string reverseString(const char* pStr);

	std::string reverseString(std::string pStr);              // (1) by value

	std::string reverseString(std::string& pStr);             // (2) lvalue ref

	std::string reverseString(const std::string& pStr);       // (3) const lvalue ref

	std::string reverseString(std::string&& pStr);            // (4) rvalue ref

	std::string reverseString(std::string* pStr);			  // (5) pointer

	std::string reverseString(const std::string* pStr);		  // (6) pointer to const

	std::string revStrConstRefArg(const std::string_view& pStr);

	std::string revStrNonConstRefArg(std::string_view& pStr);

	std::string revStrRValueRefArg(std::string_view&& pStr);

	std::string revStrOverloadValRef(std::string_view pStr);

	std::string revStrOverloadValRef(std::string_view& pStr);

	std::string revStrOverloadValCRef(std::string_view pStr);

	std::string revStrOverloadValCRef(const std::string_view& pStr);

	std::string revStrOverloadRefAndCRef(std::string_view& pStr);

	std::string revStrOverloadRefAndCRef(const std::string_view& pStr);
};