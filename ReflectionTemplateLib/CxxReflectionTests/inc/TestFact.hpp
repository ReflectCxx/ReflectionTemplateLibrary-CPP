#pragma once

#include <sstream>
#include <cassert>
#include <memory>

#include "TestFact.h"

template<class _type, class _reflTy>
constexpr void TestFact::ASSERT_STATES_EQUAL(std::unique_ptr<_type>& pPtrI, rtl::ReflObject<_reflTy>& pPtrII) const {
	assert(m_return == m_reflReturn && "Return values are not same");
	assert(*pPtrI == *(static_cast<_type*>(pPtrII.get())) && "Objects state are not same");
}

template<class _type, class _reflTy>
void TestFact::RESULT_DESCRIPTION(std::unique_ptr<_type>& pPtrI, rtl::ReflObject<_reflTy>& pPtrII) const {

	std::string bufa, bufb, bufc;
	std::stringstream ssa(pPtrI->getState()), ssb(static_cast<_type*>(pPtrII.get())->getState()), ssc(pPtrI->getState());
	std::size_t MAX_WIDTH = 0;

	while (std::getline(ssc, bufc, '\n')) {
		if (bufc.size() > MAX_WIDTH) MAX_WIDTH = bufc.size();
	}
	m_result.append("\n    (REGULAR OBJECT)" + std::string(MAX_WIDTH - 17, ' ') + "    (REFLECTION OBJECT)\n");
	while (std::getline(ssa, bufa, '\n') && std::getline(ssb, bufb, '\n'))
	{
		if (bufa.length() != 0)
		{
			const std::size_t count = (MAX_WIDTH - bufa.length());
			if (count > 0) { bufa.append(std::string(count, ' ')); }
			m_result.append("    " + bufa + "   " + bufb + "\n");
		}
		else
		{
			m_result.append(std::string(MAX_WIDTH, ' ') + "\n");
		}
	}
	if (!m_return.empty()) {
		m_result.append("    RETURN : " + m_return + std::string(MAX_WIDTH - 21, ' ') + "RETURN : " + m_reflReturn + "\n");
	}
	m_result.append("test:\tPASSED\n\n");
}