#pragma once
#include <string>

class Person
{
    mutable std::string m_address;
    mutable std::string m_lastName;
    const std::string m_firstName;

public:

    ~Person();
    Person() = delete;
    Person(const std::string& pName);

    void updateAddress(const std::string& pAddress);

    void updateAddress(const std::string& pAddress) const;

    void updateLastName(const std::string& pLastName) const;

    const bool operator==(const Person& pOther) const;

    static unsigned getInstanceCount();
};