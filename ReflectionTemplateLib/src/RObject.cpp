#include "RObject.hpp"

namespace rtl {

	std::size_t g_rObjectTypeIdCounter = 0;

	RObject::~RObject()
	{

	}

	RObject::RObject(const std::size_t& pTypeId, const std::string& pType) 
		: m_type(pType)
		, m_typeId(pTypeId)
	{

	}
}