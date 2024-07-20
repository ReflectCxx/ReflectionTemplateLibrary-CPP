#pragma once

#include <any>
#include <memory>
#include <unordered_map>

#include "TypeId.h"
#include "Constants.h"

namespace rtl {

	namespace access
	{
		class Record;
		class RStatus;
		class Function;
		
		class Instance
		{
			mutable TypeQ m_qualifier;

			const std::size_t m_typeId;

			const std::any m_anyObject;
			const std::shared_ptr<void> m_destructor;

			explicit Instance();
			explicit Instance(const std::any& pRetObj, const RStatus& pStatus, const Function& pDctor);

		public:

			Instance(const Instance&);

			GETTER(std::any, , m_anyObject);
			GETTER(std::size_t, TypeId, m_typeId);
			GETTER(TypeQ, Qualifier, m_qualifier);

			const bool isEmpty() const;
			const bool isConst() const;

			void makeConst(const bool& pCastAway = false);

			static std::size_t getInstanceCount();

			friend Record;
		};
	}
}