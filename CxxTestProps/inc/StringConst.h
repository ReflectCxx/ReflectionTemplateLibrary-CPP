#pragma once

#include <string>

// 'StrConst' - String-Const, all methods are const.
struct StrConst
{
	constexpr static const char* struct_ = "StrConst";

	std::string reverseString() const;

	std::string reverseString(const char* pStr) const;

	std::string reverseString(std::string pStr) const;					// (1) by value

	std::string reverseString(std::string& pStr) const;					// (2) lvalue ref

	std::string reverseString(const std::string& pStr) const;			// (3) const lvalue ref

	std::string reverseString(std::string&& pStr) const;				// (4) rvalue ref

	std::string reverseString(std::string* pStr) const;					// (5) pointer

	std::string reverseString(const std::string* pStr) const;			// (6) pointer to const

	std::string revStrConstRefArg(const std::string_view& pStr) const;

	std::string revStrNonConstRefArg(std::string_view& pStr) const;

	std::string revStrRValueRefArg(std::string_view&& pStr) const;

	std::string revStrOverloadValRef(std::string_view pStr) const;

	std::string revStrOverloadValRef(std::string_view& pStr) const;

	std::string revStrOverloadValCRef(std::string_view pStr) const;

	std::string revStrOverloadValCRef(const std::string_view& pStr) const;

	std::string revStrOverloadRefAndCRef(std::string_view& pStr) const;

	std::string revStrOverloadRefAndCRef(const std::string_view& pStr) const;
};