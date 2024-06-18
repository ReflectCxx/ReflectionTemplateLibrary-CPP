
#include <iostream>
#include <vector>
#include "Date.h"

using namespace std;

static int objectCount = 0;

namespace test_project
{

	Date::~Date() {
		std::cout << "\nDestructor called, ~Date(). objectCount: " << --objectCount;
	}

	Date::Date()
		: m_day(0)
		, m_month(0)
		, m_year(0)
	{
		std::cout << "\nConstructor called, Date(). objectCount: " << ++objectCount;
	}

	Date::Date(const string& pDateStr)
	{
		string strBuf;
		vector<string> date;
		for (size_t i = 0; i < pDateStr.length(); i++)
		{
			if (pDateStr.at(i) == '/')
			{
				date.push_back(strBuf);
				strBuf.clear();
			}
			else
			{
				strBuf.push_back(pDateStr.at(i));
			}
		}
		m_day = stoi(date[0]);
		m_month = stoi(date[1]);
		m_year = stoi(strBuf);

		std::cout << "\nConstructor called, Date(string). objectCount: " << ++objectCount;
	}

	const bool Date::operator==(const Date& pOther) const
	{
		return (m_day == pOther.m_day && m_month == pOther.m_month && m_year == pOther.m_year);
	}
}