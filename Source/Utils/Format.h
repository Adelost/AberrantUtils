#pragma once

#include "StringConvert.h"

#include <string>

namespace ae
{
	/** Make formating strings easier.

		Example:
		<pre>
		std::string str = Format::string("%1 %2 %3 %1") % "text" % true % 42;
		std::cout << str; // => text true 42 text
		</pre>
		*/

	class Format
	{
	public:
#pragma region NestedClasses
		class _Format : public std::string
		{
		public:
			/** Constructs StringFormat with "text" as the inputed text to be
				modified. */
			_Format(const std::string& text);
			/** Replaces occurrences of "%(number)", e.g. %1, %2, %3, in text with
				argument". Numbers are replaced in ascending order.	*/
			template<class T>
			_Format& operator%(const T& argument);
			_Format& operator%(const std::string& argument);
		};
#pragma endregion

		/** Replaces occurrences of "%(number)", e.g. %1, %2, %3, in text with
			"argument". Numbers are replaced in ascending order. */
		_Format static string(std::string text);

	};


	template<class T>
	Format::_Format& Format::_Format::operator%(const T& argument)
	{
		return (*this) % (StringConvert::toString(argument));
	}
}