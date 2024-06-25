
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

//void Book::setAuthor(const char* pAuthor) {
//	m_author = pAuthor;
//}

void Book::setAuthor(string pAuthor) {
	m_author = pAuthor;
}

//void Book::setAuthor(string& pAuthor) {
//	m_author = pAuthor;
//}

//void Book::setAuthor(const string& pAuthor) {
//	m_author = pAuthor;
//}

//string Book::getPublishedOn() const {
//	return m_date.getAsString();
//}

const bool Book::operator==(const Book& pOther) const {
	return (m_price == pOther.m_price && m_author == pOther.m_author && m_date == pOther.m_date && m_title == pOther.m_title);
}

string Book::getPublishedOn() {

	return m_date.getAsString();
}

unsigned Book::getInstanceCount() {
	return m_instanceCount;
}

void Book::updateBookInfo()
{
	m_price = 89.99;
	m_date = nsdate::Date(23, 5, 1884);
	m_title = "The Three Muskteers";
	m_author = "Alexandre Dumas";
}

void Book::updateBookInfo(const char* pTitle, double pPrice, std::string pAuthor)
{
	m_price = pPrice;
	m_date = nsdate::Date(9, 10, 2020);
	m_title = string(pTitle) + "[Discontinued]";
	m_author = pAuthor + " (Retired)";
}


void Book::updateBookInfo(std::string pAuthor, double pPrice, const char* pTitle)
{
	m_price = pPrice;
	m_date = nsdate::Date(6, 12, 1999);
	m_title = string(pTitle) + "[BestSeller]";
	m_author = pAuthor + " (Independent)";
}