
#pragma once

#include <string>
#include <memory>

namespace nsdate
{
	struct Calender;

	struct Date
	{
		Date();
		Date(const Date& pOther);
		Date(const std::string& pDateStr);
		Date(unsigned dd, unsigned mm, unsigned yy);
        Date(Date&&) noexcept;

		Date& operator=(Date&&) = default;
		Date& operator=(const Date&) = default;

		const bool operator==(const Date& pOther) const;

		~Date();

		static unsigned instanceCount();

		std::string getAsString() const;

		void updateDate(std::string pDateStr);

		std::shared_ptr<Calender> m_calender;

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