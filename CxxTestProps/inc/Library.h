
#pragma once
#include <unordered_map>

class Book;

class Library
{
	static std::unordered_map<std::string, Book> m_booksByTitle;

public:
	
	Library();
	~Library();

	Library(const Library&) = delete;

	static int getBooksCount();

	static std::size_t getInstanceCount();

	static void addBook(const Book& pBook);

	static Book getBookByTitle(const std::string& pTitle);
};