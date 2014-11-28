#include "Member.h"

#include "StringConvert.h"

char* Member::stringFromType[Last] =
{
	"Int",
	"Bool",
	"Float",
	"String",
};

Member::Member()
{

}

Member::Member( void** start, int offset, Type type, std::string name )
{
	m_start = start;
	m_offset = offset;
	m_type = type;
	m_name = name;
}



std::string Member::name()
{
	return m_name;
}

Member::Type Member::type()
{
	return m_type;
}

char* Member::typeName()
{
	return stringFromType[(int)m_type];
}

std::string Member::valueAsString()
{
	/*if (type() == Member::Int)
		return StringConvert::toString(value<int>());
	if (type() == Member::Float)
		return StringConvert::toString(value<float>());
	if (type() == Member::Bool)
		return StringConvert::toString(value<bool>());*/

	return "Unkown";
}


