#pragma once

#include <string>

class Animal
{
	std::string m_name;
	static unsigned m_instanceCount;

public:

	Animal();
	~Animal();

	void setAnimalName(std::string& pName);

	void setAnimalName(std::string&& pName);

	void setAnimalName(const std::string& pName);

	const bool operator==(const Animal& pOther) const;

	static unsigned getInstanceCount();
};