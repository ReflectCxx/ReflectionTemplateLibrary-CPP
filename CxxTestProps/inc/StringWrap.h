#pragma once

#include <string>

struct StrWrap
{
	const std::string m_str;
	const std::string& sstr() const;

	StrWrap(const std::string& pStr);
};

// 'StrWrapA' - String-Wrapper, only constructors for testing.
struct StrWrapA : public StrWrap
{
	constexpr static const char* struct_ = "StrWrapA";

	StrWrapA();

	StrWrapA(std::string_view pStr);              // (1) by value

	StrWrapA(std::string& pStr);             // (2) lvalue ref

	StrWrapA(const std::string& pStr);       // (3) const lvalue ref

	StrWrapA(std::string&& pStr);            // (4) rvalue ref

	StrWrapA(const char* pStr);			  // (5) pointer
};


// 'StrWrapB' - String-Wrapper, only constructors for testing.
struct StrWrapB : public StrWrap
{
	constexpr static const char* struct_ = "StrWrapB";
	StrWrapB(std::string& pStr);
	StrWrapB(const std::string& pStr);
};


// 'StrWrapC' - String-Wrapper, only constructors for testing.
struct StrWrapC : public StrWrap
{
	constexpr static const char* struct_ = "StrWrapC";
	StrWrapC(std::string& pStr);
};


// 'StrWrapD' - String-Wrapper, only constructors for testing.
struct StrWrapD : public StrWrap
{
	constexpr static const char* struct_ = "StrWrapD";
	StrWrapD(const std::string& pStr);
};