#include "Field.h"

#include "StringConvert.h"

namespace ae
{
	char* Field::stringFromType[TypeCount] =
	{
		"Int",
		"Bool",
		"Float",
		"String",
	};

	Field::Field()
	{

	}

	Field::Field(void** start, int offset, Type type, std::string name)
	{
		m_start = start;
		m_offset = offset;
		m_type = type;
		m_name = name;
	}

	std::string Field::name()
	{
		return m_name;
	}

	Field::Type Field::type()
	{
		return m_type;
	}

	std::string Field::typeName()
	{
		return std::string(stringFromType[(int)m_type]);
	}

	std::string Field::valueAsString()
	{
		if (type() == Field::Int)
			return StringConvert::toString(value<int>());
		if (type() == Field::Float)
			return StringConvert::toString(value<float>());
		if (type() == Field::Bool)
			return StringConvert::toString(value<bool>());

		return "Unkown";
	}
}

