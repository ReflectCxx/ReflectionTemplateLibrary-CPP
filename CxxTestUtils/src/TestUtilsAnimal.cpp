
#include "RObject.hpp"

#include "TestUtilsAnimal.h"
#include "Animal.h"
#include "Library.h"

static auto _= Library::getBooksCount();

const bool test_utils::animal::assert_zero_instance_count()
{
	return (Animal::getInstanceCount() == 0);
}


template<>
const bool test_utils::animal::test_method_updateZooKeeper<std::string&>(const std::string& pZooKeeper)
{
	std::string zooKeeper = ZOO_KEEPER;
	return (pZooKeeper == Animal::updateZooKeeper(zooKeeper));
}


template<>
const bool test_utils::animal::test_method_updateZooKeeper<std::string&&>(const std::string& pZooKeeper)
{
	return (pZooKeeper == Animal::updateZooKeeper(ZOO_KEEPER));
}


template<>
const bool test_utils::animal::test_method_updateZooKeeper<const std::string&>(const std::string& pZooKeeper)
{
	const std::string zooKeeper = ZOO_KEEPER;
	return (pZooKeeper == Animal::updateZooKeeper(zooKeeper));
}


const bool test_utils::animal::test_method_setAnimalName_rvalue_args(const rtl::RObject& pInstance)
{
	if (pInstance.canViewAs<Animal>()) 
	{
		Animal animal;
		animal.setAnimalName(std::string(NAME));

		const Animal& rAnimal = pInstance.view<Animal>()->get();
		return (animal == rAnimal);
	}
	return false;
}


const bool test_utils::animal::test_method_setAnimalName_const_lvalue_ref_args(const rtl::RObject& pInstance)
{
	if (pInstance.canViewAs<Animal>()) 
	{
		Animal animal;
		const auto& nameStr = std::string(NAME);
		animal.setAnimalName(nameStr);

		const Animal& rAnimal = pInstance.view<Animal>()->get();
		return (animal == rAnimal);
	}
	return false;
}


const bool test_utils::animal::test_method_setAnimalName_non_const_lvalue_ref_args(const rtl::RObject& pInstance)
{
	if (pInstance.canViewAs<Animal>()) 
	{
		Animal animal;
		auto nameStr = std::string(NAME);
		animal.setAnimalName(nameStr);

		const Animal& rAnimal = pInstance.view<Animal>()->get();
		return (animal == rAnimal);
	}
	return false;
}
