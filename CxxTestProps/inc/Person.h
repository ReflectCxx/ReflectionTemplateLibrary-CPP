#pragma once
#include <string>


class Person
{
    mutable std::string m_address;
    mutable std::string m_lastName;
    const std::string m_firstName;

public:

    Person();
    ~Person();
    Person(Person&&) noexcept;
    Person(const Person& pOther);
    Person(const std::string& pName);

    void updateAddress();

    void updateAddress() const;

    std::string getFirstName();

    void updateAddress(std::string pAddress);

    void updateAddress(std::string pAddress) const;

    void updateLastName(std::string pLastName) const;

    const bool operator==(const Person& pOther) const;

    static std::string getDefaults();

    static std::string getProfile();

    static std::string getProfile(bool pNoAddress);

    static std::string getProfile(std::string pOccupation, std::size_t pAge);

    static const Person createConst();

    static const Person* createPtr();

    static void deletePtr(const Person* ptr);

    static unsigned getInstanceCount();
};