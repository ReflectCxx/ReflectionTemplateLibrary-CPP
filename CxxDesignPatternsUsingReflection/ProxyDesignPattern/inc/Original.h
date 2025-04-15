#pragma once

#include <string>

namespace proxy_test {

    class Original
    {
        std::string m_nodeName; ///< The name of the node.
        const std::string m_className; ///< The name of the class.

        static unsigned int m_instanceCount; ///< The count of instances created.

    public:

        /**
         * @brief Constructs a new Original object.
         */
        Original();

        /**
         * @brief Destroys the Original object.
         */
        ~Original();

        /**
         * @brief Gets the class name.
         * @return The class name as a string.
         */
        std::string getClassName();

        /**
         * @brief Gets the square root of the given number.
         * @param pNum The number to get the square root of.
         * @return The square root of the given number.
         */
        const double getSquareRoot(const double pNum);

        /**
         * @brief Sets the node name.
         * @param pName The name to set for the node.
         */
        void setNodeName(std::string pName);

        /**
         * @brief Gets the node name.
         * @return The node name as a constant reference to a string.
         */
        const std::string& getNodeName();

        /**
         * @brief Gets the instance count.
         * @return The instance count as a constant reference to an integer.
         */
        static const int& getInstanceCount();
    };
}
