
#include <complex>

#include "Complex.h"

namespace complex
{
	static double g_imgNumber;
	static double g_realNumber;

	double getMagnitude()
	{
		std::complex<double> z(g_realNumber, g_imgNumber);
		return std::abs(z);
	}

	void setReal(double pNum) {
		g_realNumber = pNum;
	}

	void setImaginary(double pNum) {
		g_imgNumber = pNum;
	}
}


std::string getComplexNumAsString()
{
	return std::to_string(complex::g_realNumber) + "i" + (std::to_string(complex::g_imgNumber));
}


//namespace person {
//
//	float g_weight;
//	unsigned int g_age;
//	std::string g_lastName;
//	std::string g_firstName;
//
//	void setName(const char* pFirstName, const char* pLastName)
//	{
//		g_firstName = pFirstName;
//		g_lastName = pLastName;
//	}
//
//
//	void setAge(unsigned int pAge)
//	{
//		g_age = pAge;
//	}
//
//
//	void setWeight(float pWeight)
//	{
//		g_weight = pWeight;
//	}
//
//
//	void setProfile(const char* pFirstName, const char* pLastName, unsigned int pAge, float pWeight)
//	{
//		g_age = pAge;
//		g_weight = pWeight;
//		g_firstName = pFirstName;
//		g_lastName = pLastName;
//	}
//
//	std::string showProfile()
//	{
//		std::stringstream outStr;
//		outStr << "\n------Person-------\nName: " << g_firstName
//			<< " " << g_lastName
//			<< "\nAge: " << g_age
//			<< "\nWeight: " << g_weight << "\n";
//
//		return outStr.str();
//	}
//}
//
//
//namespace book {
//
//	double g_price;
//	unsigned int g_pageCount;
//	std::string g_name;
//	std::string g_author;
//
//	void setName(const std::string pBookName)
//	{
//		g_name = pBookName;
//	}
//
//	void setAuthor(const std::string pAuthor)
//	{
//		g_author = pAuthor;
//	}
//
//	void setPageCount(unsigned int pPageCount)
//	{
//		g_pageCount = pPageCount;
//	}
//
//	void setPrice(double pPrice)
//	{
//		g_price = pPrice;
//	}
//
//	void addBookInfo(const char* pBookName, std::string pAuthor, unsigned int pPageCount, double pPrice)
//	{
//		std::cout << "\nCalled book::addBookInfo(const char*, string, unsigned int, double)->void.";
//		g_name = pBookName;
//		g_author = pAuthor;
//		g_pageCount = pPageCount;
//		g_price = pPrice;
//	}
//
//	std::string showBookInfo()
//	{
//		std::cout << "\nCalled book::showBookInfo()->std::string.";
//		std::stringstream outStr;
//		outStr << "\n------Book-------\nName: " << g_name
//			<< "\nAuthor: " << g_author
//			<< "\nPages: " << g_pageCount
//			<< "\nPrice: " << g_price << "\n";
//
//		return outStr.str();
//	}
//}