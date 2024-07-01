#pragma once

#include <string>
#include <typeinfo>

namespace rtl {

	namespace detail 
	{
		template<class _type = std::nullptr_t, class ..._rest>
		struct TypeId;

		template<class _type>
		struct TypeId<_type>
		{
			static constexpr const std::size_t get() {
				return m_typeId;
			}

			static const std::string toString()
			{
				if (!std::is_same<_type, std::nullptr_t>::value) {
					return std::string(typeid(_type).name());
				}
				else return std::string();
			}

		private:
			static const std::size_t m_typeId;
		};


		// template<class ..._rest>
		// struct TypeId<std::string, _rest...>
		// {
		// 	using TAIL = TypeId<_rest...>;

		// 	static constexpr const std::size_t get() {
		// 		return m_typeId;
		// 	}

		// 	static const std::string toString()
		// 	{
		// 		const std::string& tailStr = TAIL::toString();
		// 		return ("std::string" + (tailStr.empty() ? "" : (", " + tailStr)));
		// 	}

		// private:
		// 	static const std::size_t m_typeId;
		// };


		template<class _first, class ..._rest>
		struct TypeId
		{
			using HEAD = _first;
			using TAIL = TypeId<_rest...>;

			static const std::string toString() {

				const std::string& tailStr = TAIL::toString();
				return (std::string(typeid(HEAD).name()) + ", " + tailStr);
			}
		};

		extern std::size_t g_typeIdCounter;

		template<class _type>
		const std::size_t TypeId<_type>::m_typeId = g_typeIdCounter++ ;
	}
}