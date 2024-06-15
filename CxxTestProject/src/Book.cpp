
#include <vector>
#include <iostream>
#include <sstream>

#include "Book.h"

namespace test_project
{
	using namespace std;

	const string thisStr(Book* pThis)
	{
		std::stringstream ss;
		ss << static_cast<const void*>(pThis);
		return string("__this[") + ss.str() + string("](") + string(typeid(pThis).name()) + string(")");
	}

	const string thisStr(const Book* pThis)
	{
		std::stringstream ss;
		ss << static_cast<const void*>(pThis);
		return string("__this[") + ss.str() + string("](") + string(typeid(pThis).name()) + string(")");
	}


	Book::~Book()
	{
		//cout << "\n\tbook \tdctor\t\t{ ~Book() }";
	}

	Book::Book()
		: m_price(0.0)
		, m_title("no_title")
		, m_author("no_author")
	{
		m_fuctorSignature = m_ctorSignature = "Book::Book()";
	}

	Book::Book(const Book& pOther)
		: m_price(0.0)
		, m_date(pOther.m_date)
		, m_title(pOther.m_title)
		, m_author(pOther.m_author)
	{
		m_fuctorSignature = m_ctorSignature = "Book::Book(const Book&)";
	}

	Book::Book(const string& pTitle)
		: m_price(0.0)
		, m_title(pTitle)
		, m_author("no_author")
	{
		m_fuctorSignature = m_ctorSignature = "Book::Book(const string&)";
	}

	Book::Book(double pPrice, string pTitle)
		: m_price(pPrice)
		, m_title(pTitle)
		, m_author("no_author")
	{
		m_fuctorSignature = m_ctorSignature = "Book::Book(double, string)";
	}

	Book::Book(Date& pDate, string pTitle)
		: m_price(0.0)
		, m_date(pDate)
		, m_title(pTitle)
		, m_author("no_author")
	{
		m_fuctorSignature = m_ctorSignature = "Book::Book(Date&, string)";
	}

	void Book::setPublishedOn(Date& pDate)
	{
		m_fuctorSignature = "void Book::setPublishedOn(Date&)";
		m_date = pDate;
	}

	void Book::setPublishedOn(const Date& pDate)
	{
		m_fuctorSignature = "void Book::setPublishedOn(const Date&)";
		m_date = pDate;
	}

	void Book::setPublishedOn(int pDay, int pMonth, int pYear)
	{
		m_fuctorSignature = "void Book::setPublishedOn(int, int, int)";
		m_date.m_day = pDay;
		m_date.m_month = pMonth;
		m_date.m_year = pYear;
	}

	void Book::setAuthor(const char* pAuthor)
	{
		m_fuctorSignature = "void Book::setTitle(const char*)";
		m_author = pAuthor;
	}

	void Book::setAuthor(string pAuthor)
	{
		m_fuctorSignature = "void Book::setTitle(string)";
		m_author = pAuthor;
	}

	void Book::setAuthor(string& pAuthor)
	{
		m_fuctorSignature = "void Book::setTitle(string&)";
		m_author = pAuthor;
	}

	void Book::setAuthor(const string& pAuthor)
	{
		m_fuctorSignature = "void Book::setTitle(const string&)";
		m_author = pAuthor;
	}

	std::string Book::getTitle()
	{
		m_fuctorSignature = "std::string Book::getTitle()";
		return m_title;
	}

	std::string Book::getAuthor()
	{
		m_fuctorSignature = "std::string Book::getAuthor()";
		return m_author;
	}

	string Book::getBookInfo() const
	{
		m_fuctorSignature = "string Book::getBookInfo() const";
		const string dateStr = to_string(m_date.m_day) + "/" + to_string(m_date.m_month) + "/" + to_string(m_date.m_year);
		const string info = string("{\n\tTitle:") + m_title + string(",\n\tAuthor:") + m_author + string(",\n\tPrice:") +
			to_string(m_price) + string(",\n\tPublished date:") + dateStr + string("\n}");
		return info;
	}

	string Book::getPublishedOn() const
	{
		m_fuctorSignature = "string Book::getPublishedOn() const";
		const string dateStr = to_string(m_date.m_day) + "/" + to_string(m_date.m_month) + "/" + to_string(m_date.m_year);
		return dateStr;
	}

	std::string Book::getState()
	{
		const string dateStr = to_string(m_date.m_day) + "/" + to_string(m_date.m_month) + "/" + to_string(m_date.m_year);
		const string info = string("\n") + thisStr(this) + string(" : {\n|") +
			string("\n|  Price: \"") + to_string(m_price) + string("\",") +
			string("\n|  Title: \"") + m_title + string("\",") +
			string("\n|  Author: \"") + m_author + string("\",") +
			string("\n|  PublishedOn: \"") + dateStr + string("\",") +
			string("\n|  [ctor]: { ") + m_ctorSignature + string(" },") +
			string("\n|  [method]: { ") + m_fuctorSignature + string(" }") +
			string("\n}");
		return info;
	}

	std::string Book::getState() const
	{
		const string dateStr = to_string(m_date.m_day) + "/" + to_string(m_date.m_month) + "/" + to_string(m_date.m_year);
		const string info = string("\n") + thisStr(this) + string(" : {\n|") +
			string("\n|  Price: \"") + to_string(m_price) + string("\",") +
			string("\n|  Title: \"") + m_title + string("\",") +
			string("\n|  Author: \"") + m_author + string("\",") +
			string("\n|  PublishedOn: \"") + dateStr + string("\",") +
			string("\n|  [ctor]: { ") + m_ctorSignature + string(" },") +
			string("\n|  [method]: { ") + m_fuctorSignature + string(" }") +
			string("\n}");
		return info;
	}

	const bool Book::operator==(const Book& pOther) const
	{
		return (m_price == pOther.m_price &&
			m_author == pOther.m_author &&
			m_date == pOther.m_date &&
			m_ctorSignature == pOther.m_ctorSignature &&
			m_fuctorSignature == pOther.m_fuctorSignature);
	}

	string Book::getPublishedOn()
	{
		const string dateStr = to_string(m_date.m_day) + "/" + to_string(m_date.m_month) + "/" + to_string(m_date.m_year);
		return dateStr;
	}
}