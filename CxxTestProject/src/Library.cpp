
#include "Book.h"
#include "Library.h"

std::unordered_map<std::string, Book> Library::m_booksByTitle;

Library::Library()
{
}

int Library::getBooksCount()
{
    return m_booksByTitle.size();
}

void Library::addBook(const Book& pBook)
{
	m_booksByTitle[pBook.getTitle()] = pBook;
}

Book Library::getBookByTitle(const std::string& pTitle)
{
	return m_booksByTitle[pTitle];
}