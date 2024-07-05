
#include "Person.h"

static unsigned g_instanceCount = 0;

Person::~Person()
{
	g_instanceCount--;
}

Person::Person(const std::string& pName)
	: m_address("")
	, m_lastName("")
	, m_firstName(pName)
{
	g_instanceCount++;
}

void Person::updateAddress()
{
	m_address = "No Address given. non const method called. [__updateAddress()]";
}

void Person::updateAddress() const
{
	m_address = "No Address given. const method called. [__updateAddress() const]";
}


const bool Person::operator==(const Person& pOther) const
{
	return (m_address == pOther.m_address && m_firstName == pOther.m_firstName && m_lastName == pOther.m_lastName);
}


unsigned Person::getInstanceCount()
{
	return g_instanceCount;
}


void Person::updateAddress(std::string pAddress)
{
	m_address = pAddress + " [__updateAddress(std::string)]";
}

void Person::updateAddress(std::string pAddress) const
{
	m_address = pAddress + " [__updateAddress(std::string) const]";
}

void Person::updateLastName(std::string pLastName) const
{
	m_lastName = pLastName + " [__updateLastName(std::string) const]";
}