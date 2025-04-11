
#include <cmath>
#include <iostream>
#include "Original.h"

namespace proxy_test {

	unsigned int Original::m_instanceCount = 0;

	Original::Original()
		: m_nodeName("defaultNodeName")
		, m_className("Original")
	{
		m_instanceCount++;
		std::cout << "\"Original\" constructor called, instance count: " << m_instanceCount << "\n";
	}
	
	Original::~Original()
	{
		m_instanceCount--;
		std::cout << "\"Original\" destructor called, instance count: " << m_instanceCount << "\n";
	}

	const int& Original::getInstanceCount()
	{
		return m_instanceCount;
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