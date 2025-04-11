#pragma once

#include <string>

namespace proxy_test {

	class Original 
	{
		std::string m_nodeName;
		const std::string m_className;
		
	public:

		Original();

		std::string getClassName();

		const double getSquareRoot(const double pNum);

		void setNodeName(std::string pName);

		const std::string& getNodeName();
	};
}