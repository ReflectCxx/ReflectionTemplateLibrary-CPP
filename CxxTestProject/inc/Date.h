
#include <string>

namespace test_project 
{
	struct Date
	{
		Date();
		Date(const std::string& pDateStr);
		Date(unsigned dd, unsigned mm, unsigned yy);

		const bool operator==(const Date& pOther) const;

		~Date();

		static unsigned instanceCount();

	private:

		unsigned m_day;
		unsigned m_month;
		unsigned m_year;
		static unsigned m_instanceCount;
	};
}