#pragma once

#include <string>

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