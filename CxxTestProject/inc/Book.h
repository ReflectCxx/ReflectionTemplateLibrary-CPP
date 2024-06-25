
#include <string>
#include "Date.h"


class Book
{
	double m_price;
	mutable nsdate::Date m_date;

	std::string m_title;
	std::string m_author;

	static unsigned m_instanceCount;

public:

	Book();
	Book(const Book& pOther);
	Book(double pPrice, std::string pTitle);
	Book(nsdate::Date& pDate, std::string pTitle);
	~Book();

	void setPublishedOn(nsdate::Date& pDate);
	void setPublishedOn(const nsdate::Date& pDate);

	void setAuthor(const char* pAuthor);
	void setAuthor(std::string pAuthor);
	void setAuthor(std::string& pAuthor);
	void setAuthor(const std::string& pAuthor);

	std::string getPublishedOn();
	std::string getPublishedOn() const;

	void updateBookInfo(const char* pTitle, double pPrice, std::string pAuthor);

	void updateBookInfo(std::string pAuthor, double pPrice, const char* pTitle);

	const bool operator==(const Book& pOther) const;

	static unsigned getInstanceCount();
};
