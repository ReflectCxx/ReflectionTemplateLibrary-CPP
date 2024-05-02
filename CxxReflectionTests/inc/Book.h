#pragma once

#include <string>

struct Date
{
	short m_day;
	short m_month;
	short m_year;
	Date();
	Date(const std::string& pDateStr);
	const bool operator==(const Date& pOther) const;
};


class Book
{
	double m_price;
	Date m_date;
	
	std::string m_title;
	std::string m_author;

	mutable std::string m_ctorSignature;
	mutable std::string m_fuctorSignature;

public:

	Book();
	Book(const Book& pOther);
	Book(const std::string& pTitle);
	Book(double pPrice, std::string pTitle);
	Book(Date& pDate, std::string pTitle);
	~Book();

	void setPublishedOn(Date& pDate);
	void setPublishedOn(const Date& pDate);
	void setPublishedOn(int pDay, int pMonth, int pYear);

	void setAuthor(const char* pAuthor);
	void setAuthor(std::string pAuthor);
	void setAuthor(std::string& pAuthor);
	void setAuthor(const std::string& pAuthor);

	std::string getTitle();
	std::string getAuthor();
	std::string getBookInfo() const;
	std::string getPublishedOn();
	std::string getPublishedOn() const;
	std::string getState() const;
	std::string getState();

	const bool operator==(const Book& pOther) const;
};