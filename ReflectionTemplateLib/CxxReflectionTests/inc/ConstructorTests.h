#pragma once

#include <vector>

class TestFact;

struct ConstructorTests
{
	static const std::vector<void(*)(const TestFact&)> UNIT_TEST_CASES;
};

