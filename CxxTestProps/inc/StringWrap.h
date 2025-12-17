#pragma once

#include <string>

// 'StrWrap' - String-Wrapper, only constructors for testing.
struct StrWrap
{
	const std::string m_str;

	constexpr static const char* struct_ = "StrWrap";

	StrWrap();

	StrWrap(std::string_view pStr);              // (1) by value

	StrWrap(std::string& pStr);             // (2) lvalue ref

	StrWrap(const std::string& pStr);       // (3) const lvalue ref

	StrWrap(std::string&& pStr);            // (4) rvalue ref

	StrWrap(const char* pStr);			  // (5) pointer

	const std::string& sstr() const;
};