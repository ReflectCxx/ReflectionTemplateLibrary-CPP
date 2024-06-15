#pragma once

#include <string>

namespace person
{
	std::string showProfile();

	void setName(const char* pFirstName, const char* pLastName);

	void setAge(unsigned int pAge);

	void setWeight(float pWeight);

	void setProfile(const char* pFirstName, const char* pLastName,
		unsigned int pAge, float pWeight);
}


namespace book
{
	void showBookInfo();

	void setName(const std::string pBookName);

	void setAuthor(const std::string pAuthor);

	void setPageCount(unsigned int pPageCount);

	void setPrice(double pPrice);

	void addBookInfo(const char* pBookName, std::string pAuthor,
		unsigned int pPageCount, double pPrice);
}