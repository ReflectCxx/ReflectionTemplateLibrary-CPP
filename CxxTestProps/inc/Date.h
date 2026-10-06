
#pragma once

#include <string>
#include <memory>

namespace nsdate
{
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

		static std::size_t instanceCount();

		std::string getAsString() const;

		void updateDate(std::string pDateStr);

	private:

		unsigned m_day;
		unsigned m_month;
		unsigned m_year;
		static std::size_t m_instanceCount;
	};


	struct Event;

	struct Calender
	{
		Calender();
		~Calender();
		Calender(Calender&&) noexcept;
		Calender(const Calender&);
		
		Calender& operator=(Calender&&) = delete;
		Calender& operator=(const Calender&) = delete;

		Date& getTheDate();
		Date& getSavedDate();

		const Event& getTheEvent();
		const Event& getSavedEvent();

		static void resetMoveOpsCounter();
		static std::size_t instanceCount();
		static std::size_t getMoveOpsCount();

		static Calender create();

	private:

		std::shared_ptr<Event> m_theEvent;

		std::unique_ptr<Event> m_savedEvent;

		static std::size_t m_instanceCount;

		static std::size_t m_moveOpsCount;
	};


	struct Event
	{
		~Event();

		Event(Event&&) = delete;

		static std::size_t instanceCount();

		const Date& getEventDate();

		void reset();

	private:

		Event();
		Event(const Event& pOther);

		std::unique_ptr<Date> m_date;

		static std::size_t m_instanceCount;

		static Event* create();
		static Event* createCopy(const Event& pOther);

		//friends :)
		friend Calender;

		Event& operator=(Event&&) = delete;
		Event& operator=(const Event&) = delete;
	};
}
