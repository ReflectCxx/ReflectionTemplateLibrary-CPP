#pragma once

namespace rtl {

	//template<class _T>
	//class std::enable_if<!std::is_same<_T, void>::value>::type;


	class ReflVariable {

		const unsigned int m_fieldId;

		ReflVariable(unsigned int pFieldId);

	public:

		ReflVariable() = delete;

		template<class _fieldType>
		void set();

		template<class _fieldType>
		void get();

		template<class _classType, class _fieldType>
		static const ReflVariable init(_fieldType _classType::* pFieldOffset);
	};
}