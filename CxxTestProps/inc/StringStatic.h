#pragma once

#include <string>

// 'StrStatic' - String-Static, all methods are static.
struct StrStatic
{
	constexpr static const char* struct_ = "StrStatic";

	static std::string reverseString();

	static std::string reverseString(const char* pStr);

	static std::string reverseString(std::string pStr);					// (1) by value

	static std::string reverseString(std::string& pStr);					// (2) lvalue ref

	static std::string reverseString(const std::string& pStr);			// (3) const lvalue ref

	static std::string reverseString(std::string&& pStr);				// (4) rvalue ref

	static std::string reverseString(std::string* pStr);					// (5) pointer

	static std::string reverseString(const std::string* pStr);			// (6) pointer to const

	static std::string revStrConstRefArg(const std::string_view& pStr);

	static std::string revStrNonConstRefArg(std::string_view& pStr);

	static std::string revStrRValueRefArg(std::string_view&& pStr);

	static std::string revStrOverloadValRef(std::string_view pStr);

	static std::string revStrOverloadValRef(std::string_view& pStr);

	static std::string revStrOverloadValCRef(std::string_view pStr);

	static std::string revStrOverloadValCRef(const std::string_view& pStr);

	static std::string revStrOverloadRefAndCRef(std::string_view& pStr);

	static std::string revStrOverloadRefAndCRef(const std::string_view& pStr);
};