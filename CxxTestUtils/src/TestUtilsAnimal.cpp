

#include "TestUtilsAnimal.h"
#include "Animal.h"

const bool test_utils::animal::assert_zero_instance_count()
{
	return (Animal::getInstanceCount() == 0);
}

const bool test_utils::animal::test_method_setAnimalName_rvalue_args(const std::any& pInstance)
{
	Animal* rAnimal = std::any_cast<Animal*>(pInstance);
	if (rAnimal == nullptr) {
		return false;
	}
	
	Animal animal;
	animal.setAnimalName(std::string(NAME));

	return (animal == *rAnimal);
}