
#include <cmath>
#include <iostream>
#include "Original.h"

namespace proxy_test {

	Original::Original()
		: m_nodeName("defaultNodeName")
		, m_className("Original")
	{
		std::cout << "Original constructor called\n";
	}

	std::string Original::getClassName()
	{
		return m_className;
	}

	const double Original::getSquareRoot(const double pNum)
	{
		return std::sqrt(pNum);
	}

    void Original::setNodeName(std::string pName)
    {
		m_nodeName = pName;
    }

    const std::string &Original::getNodeName()
    {
        return m_nodeName;
    }
}