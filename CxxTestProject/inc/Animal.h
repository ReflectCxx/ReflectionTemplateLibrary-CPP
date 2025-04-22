#pragma once

#include <string>

class Animal
{
	std::string m_name;
	static std::string m_zooKeeper;
	static unsigned m_instanceCount;

public:

	Animal();
	~Animal();

	const bool operator==(const Animal& pOther) const;

	void setAnimalName(std::string& pName);

	void setAnimalName(std::string&& pName);

	void setAnimalName(const std::string& pName);

	static std::string updateZooKeeper(std::string& pZooKeeper);

	static std::string updateZooKeeper(std::string&& pZooKeeper);

	static std::string updateZooKeeper(const std::string& pZooKeeper);

	static unsigned getInstanceCount();
};