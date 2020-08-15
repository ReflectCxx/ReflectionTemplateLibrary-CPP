
#include <cassert>
#include <iostream>

#include "src/TestFact.h"
#include "src/MethodCallTests.h"
#include "src/ConstructorTests.h"
#include "src/InheritanceTests.h"

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