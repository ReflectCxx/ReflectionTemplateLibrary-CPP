#include "Date.h"

#include <vector>
#include "Date.h"

using namespace std;

namespace nsdate
{
	std::size_t Date::m_instanceCount = 0;
	std::size_t Event::m_instanceCount = 0;
	std::size_t Calender::m_instanceCount = 0;
	std::size_t Calender::m_moveOpsCount = 0;

	Calender::~Calender()
	{
		m_instanceCount--;
	}

	Calender::Calender()
		: m_theEvent(std::shared_ptr<Event>(Event::create()))
		, m_savedEvent(std::unique_ptr<Event>(Event::create()))
	{
		m_instanceCount++;
	}

	Calender::Calender(const Calender& pOther)
		: m_theEvent(pOther.m_theEvent)
		, m_savedEvent(pOther.m_savedEvent ? std::unique_ptr<Event>(Event::createCopy(*pOther.m_savedEvent)) : nullptr)
	{
		m_instanceCount++;
	}

	Calender::Calender(Calender&& pOther) noexcept
		: m_theEvent(std::move(pOther.m_theEvent))
		, m_savedEvent(std::move(pOther.m_savedEvent))
	{
		m_moveOpsCount++;
		m_instanceCount++;
	}

	Calender Calender::create()
	{
		return Calender();
	}

	const Event& Calender::getTheEvent()
	{
		return *m_theEvent;
	}

	const Event& Calender::getSavedEvent()
	{
		return *m_savedEvent;
	}

	Date& Calender::getTheDate()
	{
		return *(m_theEvent->m_date);
	}

	Date& Calender::getSavedDate()
	{
		return *(m_savedEvent->m_date);
	}

	std::size_t Calender::instanceCount()
	{
		return m_instanceCount;
	}

	std::size_t Calender::getMoveOpsCount()
	{
		return m_moveOpsCount;
	}

	void Calender::resetMoveOpsCounter()
	{
		m_moveOpsCount = 0;
	}
}

namespace nsdate
{
	Event::~Event()
	{
		m_instanceCount--;
	}

	Event::Event()
		: m_date(std::make_unique<Date>())
	{
		m_instanceCount++;
	}

	Event::Event(const Event& pOther)
		: m_date(pOther.m_date ? std::make_unique<Date>(*pOther.m_date) : nullptr)
	{
		m_instanceCount++;
	}

	const Date& Event::getEventDate()
	{
		return *m_date;
	}


	void Event::reset()
	{
		//does nothing yet.
	}


	std::size_t Event::instanceCount()
	{
		return m_instanceCount;
	}

	Event* Event::create()
	{
		return new Event();
	}

	Event* Event::createCopy(const Event& pOther)
	{
		return new Event(pOther);
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
			if (pDateStr[i] == '/') {
				date.push_back(strBuf);
				strBuf.clear();
			}
			else {
				strBuf.push_back(pDateStr[i]);
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
			if (pDateStr[i] == '/') {
				date.push_back(strBuf);
				strBuf.clear();
			}
			else {
				strBuf.push_back(pDateStr[i]);
			}
		}
		m_day = stoi(date[0]);
		m_month = stoi(date[1]);
		m_year = stoi(strBuf);
	}
}