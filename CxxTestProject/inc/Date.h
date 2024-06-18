
#include <string>

namespace test_project 
{
	struct Date
	{
		short m_day;
		short m_month;
		short m_year;
		Date();
		~Date();
		Date(const std::string& pDateStr);
		const bool operator==(const Date& pOther) const;
	};
}