
#include "Animal.h"

unsigned Animal::m_instanceCount = 0;

Animal::Animal()
	: m_age(0)
	, m_weight(0.0f)
	, m_isMammal(false)
	, m_name("__no_name..")
{
	m_instanceCount++;
}

Animal::~Animal()
{
	m_instanceCount--;
}

void Animal::setAnimalName(std::string&& pName)
{
	m_name = pName + "__args_std::string&&";
}

unsigned Animal::getInstanceCount()
{
	return m_instanceCount;
}

void Animal::setAnimalName(const std::string& pName)
{
	m_name = pName + "__args_std::string";
}

const bool Animal::operator==(const Animal& pOther) const
{
	if (this == &pOther)
		return true;

	if (m_age != pOther.m_age ||
		m_weight != pOther.m_weight ||
		m_isMammal != pOther.m_isMammal ||
		m_name != pOther.m_name) {
		return false;
	}

	return true;
}