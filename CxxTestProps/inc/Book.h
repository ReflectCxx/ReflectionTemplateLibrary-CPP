#pragma once

#include <string>
#include "Date.h"


class Book
{
	double m_price;
	mutable nsdate::Date m_date;

	std::string m_title;
	std::string m_author;
	std::string m_description;

	static int m_instanceCount;

public:

	Book();
	Book(const Book& pOther);
	Book(Book&& pOther) noexcept;
	Book(double pPrice, std::string pTitle);
	~Book();

	std::string getTitle() const;
	std::string getPublishedOn();

	void setAuthor(std::string pAuthor);
	void setDescription(std::string pDesc);
	void addCopyrightTag(const std::string pPubInfo);

	void updateBookInfo();
	void updateBookInfo(const char* pTitle, double pPrice, std::string pAuthor);
	void updateBookInfo(std::string pAuthor, double pPrice, const char* pTitle);

	void addPreface(const std::string pAcknowledgements, const std::string& pPreface);

	Book& operator=(const Book& pOther) = default;
	const bool operator==(const Book& pOther) const;

	static int getInstanceCount();
};