
#include "Animal.h"

unsigned Animal::m_instanceCount = 0;
std::string Animal::m_zooKeeper = "__no_zookeeper..";


Animal::Animal()
	: m_name("__no_name..")
	, m_familyName("__no_family_ :( ")
{
	m_instanceCount++;
}


Animal::~Animal()
{
	m_instanceCount--;
}


Animal::Animal(const std::string& pFamilyName)
	: m_name("__no_name..")
	, m_familyName(pFamilyName)
{
	m_instanceCount++;
}


Animal::Animal(const Animal& pOther)
	: m_name(pOther.m_name)
	, m_familyName(pOther.m_familyName)
{
	m_instanceCount++;
}


Animal& Animal::operator=(const Animal& pOther)
{
	if (this == &pOther)
		return *this;
	m_name = pOther.m_name;
	m_familyName = pOther.m_familyName;
	return *this;
}


Animal::Animal(Animal&& pOther) noexcept
	: m_name(pOther.m_name)
	, m_familyName(pOther.m_familyName)
{
	m_instanceCount++;
	pOther.m_name.clear();
	pOther.m_familyName.clear();
}


Animal& Animal::operator=(Animal&& pOther)  noexcept
{
	if (this == &pOther)
		return *this;

	m_name = pOther.m_name + "__move_assignment";
	m_familyName = pOther.m_familyName + "__move_assignment";

	pOther.m_name.clear();
	pOther.m_familyName.clear();
	return *this;
}


void Animal::setAnimalName(std::string& pName)
{
	m_name = pName + "__args_non_const_lvalue_ref...";
}


void Animal::setFamilyName(const std::string pName)
{
	m_familyName = pName;
}


std::string Animal::getFamilyName() const
{
	return m_familyName;
}


void Animal::setAnimalName(std::string&& pName)
{
	m_name = pName + "__args_rvalue_ref...";
}


unsigned Animal::getInstanceCount()
{
	return m_instanceCount;
}


void Animal::setAnimalName(const std::string& pName)
{
	m_name = pName + "__args_const_lvalue_ref...";
}


void Animal::setAnimalName(const std::string& pName) const
{
	m_name = pName + "__args_const_lvalue_ref_method_const...";
}


std::string Animal::updateZooKeeper(std::string& pZooKeeper)
{
	m_zooKeeper = pZooKeeper + "__args_non_const_lvalue_ref...";
	return m_zooKeeper;
}


std::string Animal::updateZooKeeper(std::string&& pZooKeeper)
{
	m_zooKeeper = pZooKeeper + "__args_rvalue_ref...";
	return m_zooKeeper;
}


std::string Animal::updateZooKeeper(const std::string& pZooKeeper)
{
	m_zooKeeper = pZooKeeper + "__args_const_lvalue_ref...";
	return m_zooKeeper;
}


const bool Animal::operator==(const Animal& pOther) const
{
	if (this == &pOther)
		return true;

	if (m_name != pOther.m_name || m_familyName != pOther.m_familyName) {
		return false;
	}

	return true;
}