#pragma once

#include <vector>

class TestFact;

struct InheritanceTests
{
	static const std::vector<void(*)(const TestFact&)> UNIT_TEST_CASES;
};

