#pragma once

#include <string>

class Person
{
    int m_age;
    std::string m_name;

public:

    Person(std::string pName, int pAge)
        : m_age(pAge)
        , m_name(pName)
    { }

    int getAge() {
        return m_age;
    }

    void setAge(const int pAge) {
        m_age = pAge;
    }

    std::string getName() {
        return m_name;
    }
};