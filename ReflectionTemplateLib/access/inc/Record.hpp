#include <cassert>

#include "Record.h"
#include "RStatus.h"
#include "Method.h"
#include "Constants.h"

namespace rtl {

	namespace access
	{
		template<class ..._ctorArgs>
		inline const std::pair<RStatus, Instance> Record::instance(_ctorArgs ...params) const
		{
			const std::string& ctorName = (m_recordName + CTOR_SUFFIX);
			const std::string& dctorName = (m_recordName + DCTOR_SUFFIX);
			const std::string& constConverterName = (m_recordName + CONST_CONVERTER_SUFFIX);

			const auto& itr = m_methods.find(ctorName);
			if (itr != m_methods.end()) {
				const RStatus& ret = itr->second.invokeCtor(params...);
				if (ret.didCallSucceed()) 
				{
					const Function dctor = getMethod(dctorName).value();
					const Function toConst = getMethod(constConverterName).value();
					return std::make_pair(ret, Instance(ret.get(), ret.getTypeId(), TypeQ::Mute, dctor, toConst));
				}
			}
			else {
				assert(false && "constructor with the given args, not found.");
			}
			return std::make_pair(RStatus(false), Instance());
		}
	}
}