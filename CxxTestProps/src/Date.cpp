
#include <vector>
#include "Date.h"

using namespace std;

namespace nsdate
{
	std::size_t Date::m_instanceCount = 0;
	std::size_t Event::m_instanceCount = 0;
	std::size_t Calender::m_instanceCount = 0;

	Calender::Calender()
		:m_event(std::shared_ptr<Event>(Event::create()))
	{
		m_instanceCount++;
	}

	Calender::~Calender()
	{
		m_instanceCount--;
	}

	Calender::Calender(const Calender& pOther)
		:m_event(pOther.m_event)
	{
		m_instanceCount++;
	}

	const Event& Calender::getTheEvent()
	{
		return *m_event;
	}

	const Date& Calender::getTheDate()
	{
		return *(m_event->m_edate);
	}

	std::size_t Calender::instanceCount()
	{
		return m_instanceCount;
	}
}

namespace nsdate
{
	Event::Event()
		:m_edate(std::make_shared<Date>())
	{
		m_instanceCount++;
	}

	Event::~Event() 
	{
		m_instanceCount--;
	}

	const Date& Event::getEventDate()
	{
		return *m_edate;
	}

	std::size_t Event::instanceCount()
	{
		return m_instanceCount;
	}

	Event* Event::create()
	{
		return new Event();
	}
}


namespace nsdate 
{
	Date::~Date() {
		m_instanceCount--;
	}

	std::size_t Date::instanceCount()
	{
		return m_instanceCount;
	}

	std::string Date::getAsString() const
	{
		return (to_string(m_day) + "/" + to_string(m_month) + "/" + to_string(m_year));
	}


	void Date::updateDate(std::string pDateStr)
	{
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

	Date::Date()
		: m_day(1)
		, m_month(1)
		, m_year(2000) 
	{
		m_instanceCount++;
	}

	Date::Date(const Date& pOther)
		: m_day(pOther.m_day)
		, m_month(pOther.m_month)
		, m_year(pOther.m_year)
	{
		m_instanceCount++;
	}

	Date::Date(unsigned dd, unsigned mm, unsigned yy)
		: m_day(dd)
		, m_month(mm)
		, m_year(yy)
	{
		m_instanceCount++;
	}

	Date::Date(Date&& pOther) noexcept
		: m_day(pOther.m_day)
		, m_month(pOther.m_month)
		, m_year(pOther.m_year)
	{
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