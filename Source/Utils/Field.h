#pragma once

#include <string>

namespace ae
{
	class Field
	{
	public:
		enum Type
		{
			Int,
			Bool,
			Float,
			String,
			
			TypeCount
		};

		Field();
		Field(void** start, int offset, Field::Type type, std::string name);

		template<class T> T& value();
		std::string valueAsString();
		Type type();
		std::string typeName();
		std::string name();

	private:
		void** m_start;
		int m_offset;
		Type m_type;
		std::string m_name;

		static char* stringFromType[TypeCount];
	};

	template<class T>
	T& Field::value()
	{
		T& value = *(T*)((int)(*m_start) + m_offset);
		return value;
	}
}
