#pragma once

#include <string>
#include <sstream> // ostringstream

namespace ae
{
	/** Utility class to facilitate strings conversion. Does not support any robust
		error handling. */
	class StringConvert
	{
	public:
		/** Converts any input supporting standard output stream to text. */
		template<class T>
		static std::string toString(const T& in);
		static std::string toString(bool in);
		/** Converts string to int. Returns 0 on fail. */
		static int toInt(std::string s);
		/** Converts string to float. Returns 0.0f on fail. */
		static float toFloat(std::string s);
	};

	template<class T>
	std::string StringConvert::toString(const T& in)
	{
		std::ostringstream ss;
		ss << in;

		return ss.str();
	}
}