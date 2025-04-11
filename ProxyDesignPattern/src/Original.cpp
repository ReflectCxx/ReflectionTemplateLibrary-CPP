#include <cmath>
#include <iostream>
#include "Original.h"

namespace proxy_test {

    unsigned int Original::m_instanceCount = 0;

    /**
     * @brief Constructs a new Original object.
     *
     * Initializes the node name to "defaultNodeName" and the class name to "Original".
     * Increments the instance count and prints a message indicating the constructor call.
     */
    Original::Original()
        : m_nodeName("defaultNodeName")
        , m_className("Original")
    {
        m_instanceCount++;
        std::cout << "\"Original\" constructor called, instance count: " << m_instanceCount << "\n";
    }

    /**
     * @brief Destroys the Original object.
     *
     * Decrements the instance count and prints a message indicating the destructor call.
     */
    Original::~Original()
    {
        m_instanceCount--;
        std::cout << "\"Original\" destructor called, instance count: " << m_instanceCount << "\n";
    }

    /**
     * @brief Gets the instance count.
     * @return The instance count as a constant reference to an integer.
     */
    const int& Original::getInstanceCount()
    {
        return m_instanceCount;
    }

    /**
     * @brief Gets the class name.
     * @return The class name as a string.
     */
    std::string Original::getClassName()
    {
        return m_className;
    }

    /**
     * @brief Gets the square root of the given number.
     * @param pNum The number to get the square root of.
     * @return The square root of the given number.
     */
    const double Original::getSquareRoot(const double pNum)
    {
        return std::sqrt(pNum);
    }

    /**
     * @brief Sets the node name.
     * @param pName The name to set for the node.
     */
    void Original::setNodeName(std::string pName)
    {
        m_nodeName = pName;
    }

    /**
     * @brief Gets the node name.
     * @return The node name as a constant reference to a string.
     */
    const std::string& Original::getNodeName()
    {
        return m_nodeName;
    }
}
