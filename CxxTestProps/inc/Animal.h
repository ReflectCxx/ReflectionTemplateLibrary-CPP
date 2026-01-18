#pragma once

#include <string>
#include <memory>

class Animal
{
	mutable std::string m_name;
	std::string m_familyName;

	static std::string m_zooKeeper;
	static unsigned m_instanceCount;

public:

	Animal();
	~Animal();
	Animal(const std::string& pFamilyName);

	Animal(Animal&& pOther)  noexcept;

	Animal& operator=(Animal&& pOther) noexcept;

	Animal(const Animal& pOther);

	Animal& operator=(const Animal& pOther);

	const bool operator==(const Animal& pOther) const;

	void setFamilyName(const std::string pName);

	std::string getFamilyName() const;

	void setAnimalName(std::string& pName);

	void setAnimalName(std::string&& pName);

	void setAnimalName(const std::string& pName);

	void setAnimalName(const std::string& pName) const;

	static std::string updateZooKeeper(std::string& pZooKeeper);

	static std::string updateZooKeeper(std::string&& pZooKeeper);

	static std::string updateZooKeeper(const std::string& pZooKeeper);

	static unsigned getInstanceCount();
};