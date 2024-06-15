#include <iostream>

#include "NSFunction.h"

namespace person {

	float g_weight;
	unsigned int g_age;
	std::string g_lastName;
	std::string g_firstName;

	void setName(const char* pFirstName, const char* pLastName)
	{
		g_firstName = pFirstName;
		g_lastName = pLastName;
	}


	void setAge(unsigned int pAge)
	{
		g_age = pAge;
	}


	void setWeight(float pWeight)
	{
		g_weight = pWeight;
	}


	void setProfile(const char* pFirstName, const char* pLastName, unsigned int pAge, float pWeight)
	{
		g_age = pAge;
		g_weight = pWeight;
		g_firstName = pFirstName;
		g_lastName = pLastName;
	}

	std::string showProfile()
	{
		std::cout << "\n------Person-------\nName: " << g_firstName
			<< " " << g_lastName
			<< "\nAge: " << g_age
			<< "\nWeight: " << g_weight << "\n";

		return "xxo";
	}
}


namespace book {

	double g_price;
	unsigned int g_pageCount;
	std::string g_name;
	std::string g_author;

	void setName(const std::string pBookName)
	{
		g_name = pBookName;
	}

	void setAuthor(const std::string pAuthor)
	{
		g_author = pAuthor;
	}

	void setPageCount(unsigned int pPageCount)
	{
		g_pageCount = pPageCount;
	}

	void setPrice(double pPrice)
	{
		g_price = pPrice;
	}

	void addBookInfo(const char* pBookName, std::string pAuthor, unsigned int pPageCount, double pPrice)
	{
		g_name = pBookName;
		g_author = pAuthor;
		g_pageCount = pPageCount;
		g_price = pPrice;
	}

	void showBookInfo()
	{
		std::cout << "\n------Book-------\nName: " << g_name
			<< "\nAuthor: " << g_author
			<< "\nPages: " << g_pageCount
			<< "\nPrice: " << g_price << "\n";
	}
}