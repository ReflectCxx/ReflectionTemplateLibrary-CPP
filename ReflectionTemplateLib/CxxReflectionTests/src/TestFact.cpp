
#include <vector>

#include "TestFact.h"
#include "TestConstants.h"

using namespace std;

TestFact::TestFact() 
	: m_fact("")
	, m_result("")
	, m_return("")
	, m_reflReturn("")
	,m_expectation("")
{
}

const std::string& TestFact::fact() const 
{ 
	return m_fact; 
}

const std::string& TestFact::result() const 
{ 
	return m_result; 
}

const std::string& TestFact::expectation() const 
{ 
	return m_expectation; 
}

void TestFact::TEST(const std::string& pFact) const {
	m_fact = pFact;
}

void TestFact::EXPECTATION(const std::string& pExpectation) const {
	m_expectation = std::string("fact:\t") + pExpectation;
}