#include "Format.h"

#include "Math.h"

#include <regex>
#include <string>

namespace ae
{
	namespace
	{
		bool findSmallestNumberInString(const std::string& str, const std::string& numberPrefix, int* minNum)
		{
			std::string s = str;

			bool found = false;
			*minNum = Math::INT32_MAX;

			std::smatch sm;
			std::regex e(numberPrefix + "(\\d+)");

			while (std::regex_search(s, sm, e))
			{
				int num = ae::StringConvert::toInt(sm[1]);

				if (num < *minNum)
					*minNum = num;

				found = true;

				s = sm.suffix().str();
			}

			return found;
		}
	}

	Format::_Format& Format::_Format::operator%(const std::string& argument)
	{
		int minNum = 0;
		bool found = findSmallestNumberInString(*this, std::string("%"), &minNum);

		if (found)
			(*this).assign(std::regex_replace(*this, std::regex("%" + StringConvert::toString(minNum)), argument));

		return *this;
	}

	Format::_Format::_Format(const std::string& text)
	{
		(*this).assign(text);
	}

	Format::_Format Format::string(std::string text)
	{
		return _Format(text);
	}

}