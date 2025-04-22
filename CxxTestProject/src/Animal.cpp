
#include "Animal.h"

unsigned Animal::m_instanceCount = 0;
std::string Animal::m_zooKeeper = "__no_zookeeper..";


Animal::Animal()
	: m_name("__no_name..")
{
	m_instanceCount++;
}


Animal::~Animal()
{
	m_instanceCount--;
}


void Animal::setAnimalName(std::string& pName)
{
	m_name = pName + "__args_non_const_lvalue_ref...";
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

	if (m_name != pOther.m_name) {
		return false;
	}

	return true;
}