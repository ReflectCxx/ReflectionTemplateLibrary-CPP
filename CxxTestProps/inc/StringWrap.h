#pragma once

#include <string>

// 'StrWrap' - String-Wrapper, only constructors for testing.
struct StrWrap
{
	constexpr static const char* struct_ = "StrWrap";

	StrWrap();

	StrWrap(const char* pStr);

	StrWrap(std::string pStr);              // (1) by value

	StrWrap(std::string& pStr);             // (2) lvalue ref

	StrWrap(const std::string& pStr);       // (3) const lvalue ref

	StrWrap(std::string&& pStr);            // (4) rvalue ref

	StrWrap(std::string* pStr);			  // (5) pointer

	StrWrap(const std::string* pStr);		  // (6) pointer to const

	StrWrap(const std::string_view& pStr);

	StrWrap(std::string_view& pStr);

	StrWrap(std::string_view&& pStr);

	StrWrap(std::string_view pStr);

	//StrWrap(std::string_view& pStr);

	//StrWrap(std::string_view pStr);

	//StrWrap(const std::string_view& pStr);

	//StrWrap(std::string_view& pStr);

	//StrWrap(const std::string_view& pStr);
};