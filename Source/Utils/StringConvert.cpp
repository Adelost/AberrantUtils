#include "StringConvert.h"

#include <sstream> // stringstream

namespace ae
{
	int StringConvert::toInt(std::string s)
	{
		int n;
		std::stringstream ss(s);
		ss >> n;
		if (ss.fail())
			n = 0;

		return n;
	}

	float StringConvert::toFloat(std::string s)
	{
		float n;
		std::stringstream ss(s);
		ss >> n;
		if (ss.fail())
			n = 0.0f;

		return n;
	}

	std::string StringConvert::toString(bool in)
	{
		if (in)
			return "true";

		return "false";
	}
}
