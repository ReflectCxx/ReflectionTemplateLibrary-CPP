#pragma once

#include <string>

class Animal
{
	int m_age;
	float m_weight;
	bool m_isMammal;
	std::string m_name;

	static unsigned m_instanceCount;

public:

	Animal();
	~Animal();

	void setAnimalName(std::string&& pName);

	void setAnimalName(const std::string& pName);

	//void setAge(int a);

	//int getAge() const;

	//void setWeight(float w);

	//float getWeight() const;

	//const char* getName() const;

	//void setIsMammal(bool m);

	//bool getIsMammal() const;

	const bool operator==(const Animal& pOther) const;

	static unsigned getInstanceCount();
};