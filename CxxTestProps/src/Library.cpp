
#include "Book.h"
#include "Library.h"

std::size_t g_instanceCount = 0;

std::unordered_map<std::string, Book> Library::m_booksByTitle;

Library::Library()
{
	g_instanceCount++;
}

Library::~Library()
{
	g_instanceCount--;
}

std::size_t Library::getInstanceCount()
{
	return g_instanceCount;
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