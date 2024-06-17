#pragma once

namespace rtl {

	template<unsigned int _index, class _first, class ..._rest>
	struct TypeDescriptorList;

	template<unsigned int _index, class ..._rest>
	struct TypeDescriptorList<_index, std::nullptr_t, _rest...>
	{
		using HEAD = std::nullptr_t;

		template<class ..._args>
		inline static void call(const int pSignatureId, const int pFunctorId, _args...params)
		{
		}

		inline static void init()
		{
		}
	};


	template<unsigned int _index, class _first, class ..._rest>
	struct TypeDescriptorList
	{
		using HEAD = _first;
		using TAIL = TypeDescriptorList<_index + 1, _rest...>;

		inline static void init()
		{
			HEAD::setId(_index);
			TAIL::init();
		}

		template<class ..._args>
		inline static void call(const int pSignatureId, const int pFunctorId, _args...params)
		{
			if (_index == pSignatureId) {
				HEAD::dispatchCall(pFunctorId, params...);
			}
			else {
				TAIL::call(pSignatureId, pFunctorId, params...);
			}
		}
	};
}