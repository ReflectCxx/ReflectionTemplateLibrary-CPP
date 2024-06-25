
#include <vector>
#include <iostream>
#include <sstream>

#include "Book.h"

using namespace std;
using namespace nsdate;

unsigned Book::m_instanceCount = 0;

Book::~Book() {
	m_instanceCount--;
}

Book::Book()
	: m_price(0.0)
	, m_title("no_title_type_void")
	, m_author("no_author_type_void") {
	m_instanceCount++;
}

Book::Book(const Book& pOther)
	: m_price(pOther.m_price)
	, m_date(pOther.m_date)
	, m_title(pOther.m_title)
	, m_author(pOther.m_author) {
	m_instanceCount++;
}

Book::Book(double pPrice, string pTitle)
	: m_price(pPrice)
	, m_title(pTitle)
	, m_author("no_author_type_double_string")
	, m_date(1, 1, 1800) {
	m_instanceCount++;
}

Book::Book(Date& pDate, string pTitle)
	: m_price(9.9)
	, m_date(pDate)
	, m_title(pTitle)
	, m_author("no_author_type_date_string") {
	m_instanceCount++;
}

void Book::setPublishedOn(Date& pDate) {
	m_date = pDate;
}

void Book::setPublishedOn(const Date& pDate) {
	m_date = pDate;
}

void Book::setAuthor(const char* pAuthor) {
	m_author = pAuthor;
}

void Book::setAuthor(string pAuthor) {
	m_author = pAuthor;
}

void Book::setAuthor(string& pAuthor) {
	m_author = pAuthor;
}

void Book::setAuthor(const string& pAuthor) {
	m_author = pAuthor;
}

//string Book::getPublishedOn() const {
//	return m_date.getAsString();
//}

const bool Book::operator==(const Book& pOther) const {
	return (m_price == pOther.m_price && m_author == pOther.m_author && m_date == pOther.m_date);
}

string Book::getPublishedOn() {
	return m_date.getAsString();
}

unsigned Book::getInstanceCount() {
	return m_instanceCount;
}

void Book::updateBookInfo(const char* pTitle, double pPrice, std::string pAuthor)
{
}

void Book::updateBookInfo(std::string pAuthor, double pPrice, const char* pTitle)
{
}