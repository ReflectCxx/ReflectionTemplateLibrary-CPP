
#pragma once

#include <string>

namespace nsdate
{
	struct Date
	{
		Date();
		Date(const Date& pOther);
		Date(const std::string& pDateStr);
		Date(unsigned dd, unsigned mm, unsigned yy);

		const bool operator==(const Date& pOther) const;

		~Date();

		static unsigned instanceCount();

		std::string getAsString() const;

		void updateDate(std::string pDateStr);

	private:

		unsigned m_day;
		unsigned m_month;
		unsigned m_year;
		static unsigned m_instanceCount;
	};


	//for testing 'copy constructor not defined/disabled'
	struct Calender 
	{
		Calender();
		~Calender();

		Calender(const Calender& pOther) = delete;

		static unsigned instanceCount();

	private:
		static unsigned m_instanceCount;
	};
}