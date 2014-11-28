#pragma once

#include <string>

class Member
{
public:
	enum Type
	{
		Int,
		Bool,
		Float,
		String,
		Last,
	};

	Member();
	Member(void** start, int offset, Member::Type type, std::string name);

	template<class T> T& value();
	std::string valueAsString();
	Type type();
	char* typeName();
	std::string name();

private:
	void** m_start;
	int m_offset;
	Type m_type;
	std::string m_name;

	static char* stringFromType[Last];
};

template<class T>
T& Member::value()
{
	T& value = *(T*)((int)(*m_start) + m_offset);
	return value;
}