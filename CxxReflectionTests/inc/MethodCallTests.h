#pragma once

#include <vector>

class TestFact;

struct MethodCallTests
{
	static const std::vector<void(*)(const TestFact&)> UNIT_TEST_CASES;
};

