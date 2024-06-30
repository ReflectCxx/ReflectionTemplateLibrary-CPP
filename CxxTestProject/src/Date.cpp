
#include <iostream>
#include <vector>
#include "Date.h"

using namespace std;

static int objectCount = 0;

namespace nsdate
{
	unsigned int Date::m_instanceCount = 0;

	Date::~Date() {
		m_instanceCount--;
	}

	unsigned Date::instanceCount()
	{
		return m_instanceCount;
	}


	std::string Date::getAsString()
	{
		return (to_string(m_day) + "/" + to_string(m_month) + "/" + to_string(m_year));
	}


	Date::Date()
		: m_day(1)
		, m_month(1)
		, m_year(2000) {
		m_instanceCount++;
	}

	Date::Date(const Date& pOther)
		: m_day(pOther.m_day)
		, m_month(pOther.m_month)
		, m_year(pOther.m_year) {
		m_instanceCount++;
	}

	Date::Date(unsigned dd, unsigned mm, unsigned yy)
		: m_day(dd)
		, m_month(mm)
		, m_year(yy) {
		m_instanceCount++;
	}

	const bool Date::operator==(const Date& pOther) const
	{
		return (m_day == pOther.m_day && m_month == pOther.m_month && m_year == pOther.m_year);
	}

	Date::Date(const string& pDateStr)
	{
		m_instanceCount++;
		string strBuf;
		vector<string> date;
		for (size_t i = 0; i < pDateStr.length(); i++)
		{
			if (pDateStr.at(i) == '/') {
				date.push_back(strBuf);
				strBuf.clear();
			}
			else {
				strBuf.push_back(pDateStr.at(i));
			}
		}
		m_day = stoi(date[0]);
		m_month = stoi(date[1]);
		m_year = stoi(strBuf);
	}
}