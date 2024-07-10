
#include "Person.h"

static unsigned g_instanceCount = 0;

Person::~Person()
{
	g_instanceCount--;
}

Person::Person()
	: m_address("182 st. Westoros, Dune.")
	, m_lastName("Doe")
	, m_firstName("Jon")
{
	g_instanceCount++;
}

Person::Person(const std::string& pName)
	: m_address("__ctor_Person(const string&)")
	, m_lastName("__ctor_Person(const string&)")
	, m_firstName(pName)
{
	g_instanceCount++;
}

Person::Person(Person& pOther)
	: m_address(pOther.m_address + ".__Person::Person(Person&)")
	, m_lastName(pOther.m_lastName + ".__Person::Person(Person&)")
	, m_firstName(pOther.m_firstName + ".__Person::Person(Person&)")
{
}

Person::Person(const Person& pOther)
	: m_address(pOther.m_address + ".__Person::Person(const Person&)")
	, m_lastName(pOther.m_lastName + ".__Person::Person(const Person&)")
	, m_firstName(pOther.m_firstName + ".__Person::Person(const Person&)")
{
}

unsigned Person::getInstanceCount()
{
	return g_instanceCount;
}


void Person::updateAddress()
{
	m_address = "No Address given. non const method called. [__Person::updateAddress()]";
}


void Person::updateAddress() const
{
	m_address = "No Address given. const method called. [__Person::updateAddress() const]";
}


const bool Person::operator==(const Person& pOther) const
{
	return (m_address == pOther.m_address && m_firstName == pOther.m_firstName && m_lastName == pOther.m_lastName);
}


std::string Person::getDefaults()
{
	Person obj;
	return (obj.m_firstName + " " + obj.m_lastName + "\n" + obj.m_address);
}


std::string Person::getProfile()
{
	Person obj;
	return (obj.m_firstName + " " + obj.m_lastName + "\n" + obj.m_address + "\n[__Person::getProfile()]");
}


std::string Person::getProfile(std::string pOccupation, std::size_t pAge)
{
	Person obj;
	return (obj.m_firstName + " " + obj.m_lastName + "\n" + obj.m_address + "\n" + pOccupation +
		"\nAge: " + std::to_string(pAge) + "\n[__Person::getProfile(string, size_t)]");
}


std::string Person::getProfile(bool pNoAddress)
{
	Person obj;
	if (pNoAddress) {
		return (obj.m_firstName + " " + obj.m_lastName + "\n[__Person::getProfile(bool)__noAddress]");
	}
	else {
		return (obj.m_firstName + " " + obj.m_lastName + "\n" + obj.m_address + "\n[__Person::getProfile(bool)__withAddress]");
	}
}


void Person::updateAddress(std::string pAddress)
{
	m_address = pAddress + " [__Person::updateAddress(std::string)]";
}


void Person::updateAddress(std::string pAddress) const
{
	m_address = pAddress + " [__Person::updateAddress(std::string) const]";
}


void Person::updateLastName(std::string pLastName) const
{
	m_lastName = pLastName + " [__Person::updateLastName(std::string) const]";
}