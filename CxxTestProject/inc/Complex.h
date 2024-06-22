#pragma once

#include <string>

std::string getComplexNumAsString();

namespace complex 
{
	double getMagnitude();

	void setReal(double pNum);

	void setImaginary(double pNum);
}


//namespace person
//{
//	std::string showProfile();
//
//	void setName(const char* pFirstName, const char* pLastName);
//
//	void setAge(unsigned int pAge);
//
//	void setWeight(float pWeight);
//
//	void setProfile(const char* pFirstName, const char* pLastName,
//		unsigned int pAge, float pWeight);
//}
//
//
//namespace book
//{
//	std::string showBookInfo();
//
//	void setName(const std::string pBookName);
//
//	void setAuthor(const std::string pAuthor);
//
//	void setPageCount(unsigned int pPageCount);
//
//	void setPrice(double pPrice);
//
//	void addBookInfo(const char* pBookName, std::string pAuthor,
//		unsigned int pPageCount, double pPrice);
//}