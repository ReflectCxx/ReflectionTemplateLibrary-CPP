
#include <string>
#include "Date.h"


class Book
{
	double m_price;
	mutable nsdate::Date m_date;

	std::string m_title;
	std::string m_author;
	std::string m_description;

	static unsigned m_instanceCount;

public:

	Book();
	Book(double pPrice, std::string pTitle);
	~Book();

	std::string getPublishedOn();

	void setAuthor(std::string pAuthor);

	void updateBookInfo();
	void updateBookInfo(const char* pTitle, double pPrice, std::string pAuthor);
	void updateBookInfo(std::string pAuthor, double pPrice, const char* pTitle);

	const bool operator==(const Book& pOther) const;

	static unsigned getInstanceCount();
};
