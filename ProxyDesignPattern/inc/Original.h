#pragma once

#include <string>

namespace proxy_test {

	class Original 
	{
		std::string m_nodeName;
		const std::string m_className;

		static unsigned int m_instanceCount;

	public:

		Original();
		~Original();

		std::string getClassName();

		const double getSquareRoot(const double pNum);

		void setNodeName(std::string pName);

		const std::string& getNodeName();

		static const int& getInstanceCount();
	};
}