
#include <cassert>
#include <iostream>

#include "TestFact.h"
#include "MethodCallTests.h"
#include "ConstructorTests.h"
#include "InheritanceTests.h"

template<class _testsType>
void runRTLUnitTests()
{
	for (const auto performTest : _testsType::UNIT_TEST_CASES)
	{
		const TestFact testObject;
		
		performTest(testObject);

		std::cout	<< "\n\n************************[" << testObject.fact() << "]*************************\n"
					<< "\n" << testObject.expectation() << "\n" << testObject.result() << "\n";
	}
}

int main()
{
	runRTLUnitTests< ConstructorTests >();
	runRTLUnitTests< MethodCallTests >();
	runRTLUnitTests< InheritanceTests >();
}