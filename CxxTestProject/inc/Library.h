
#pragma once
#include <unordered_map>

#include "Book.h"

class Library
{
	static std::unordered_map<std::string, Book> m_booksByTitle;

public:
	
	Library();

	static void addBook(const Book& pBook);

	static Book getBookByTitle(const std::string& pTitle);
};