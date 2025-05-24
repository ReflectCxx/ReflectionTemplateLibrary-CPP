
#include "RObjectConverters.hpp"
#include "RObjectConvertersInit.hpp"

namespace rtl::detail
{
	using _safePODTypes = std::tuple< bool, char, signed char, unsigned char, short, unsigned short, int>;

	void RObjectConverterInit::registerConverters()
	{
		auto conversions = make_conversion_pairs<_safePODTypes>();
		register_all_conversions<decltype(conversions)>();

		RObjectConverter<std::string>::pushConversion<const char*>();
		RObjectConverter<std::string>::pushConversion<std::string_view>();
	}
}