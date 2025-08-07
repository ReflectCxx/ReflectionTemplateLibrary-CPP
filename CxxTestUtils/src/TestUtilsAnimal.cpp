

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


const bool test_utils::animal::test_method_setAnimalName_rvalue_args(const std::any& pInstance, bool pCastAsPtr)
{
	Animal animal;
	animal.setAnimalName(std::string(NAME));

	if (pCastAsPtr) {
		const Animal* rAnimal = std::any_cast<const Animal*>(pInstance);
		if (rAnimal == nullptr) {
			return false;
		}
		return (animal == *rAnimal);
	}
	else {
		auto rAnimal = std::any_cast<Animal>(&pInstance);
		return (animal == *rAnimal);
	}
}


const bool test_utils::animal::test_method_setAnimalName_const_lvalue_ref_args(const std::any& pInstance, bool pCastAsPtr)
{
	Animal animal;
	const auto& nameStr = std::string(NAME);
	animal.setAnimalName(nameStr);

	if (pCastAsPtr) {
		const Animal* rAnimal = std::any_cast<const Animal*>(pInstance);
		if (rAnimal == nullptr) {
			return false;
		}
		return (animal == *rAnimal);
	}
	else {
		auto rAnimal = std::any_cast<Animal>(&pInstance);
		return (animal == *rAnimal);
	}
}


const bool test_utils::animal::test_method_setAnimalName_non_const_lvalue_ref_args(const std::any& pInstance, bool pCastAsPtr)
{
	Animal animal;
	auto nameStr = std::string(NAME);
	animal.setAnimalName(nameStr);

	if (pCastAsPtr) {
		const Animal* rAnimal = std::any_cast<const Animal*>(pInstance);
		if (rAnimal == nullptr) {
			return false;
		}
		return (animal == *rAnimal);
	}
	else {
		auto rAnimal = std::any_cast<Animal>(&pInstance);
		return (animal == *rAnimal);
	}
}
