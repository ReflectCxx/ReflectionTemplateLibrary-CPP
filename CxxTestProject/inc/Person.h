#pragma once
#include <string>

class Person
{
    mutable std::string m_address;
    mutable std::string m_lastName;
    const std::string m_firstName;

public:

    ~Person();
    Person();
    Person(const std::string& pName);

    void updateAddress();

    void updateAddress() const;

    void updateAddress(std::string pAddress);

    void updateAddress(std::string pAddress) const;

    void updateLastName(std::string pLastName) const;

    const bool operator==(const Person& pOther) const;

    static std::string getDefaults();

    static unsigned getInstanceCount();
};