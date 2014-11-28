#pragma once

#include <string>
#include <fstream>

namespace ae
{
	class FileOpener
	{
	public:
		FileOpener(const char* path);
		~FileOpener();

		void write(std::string text);

	private:
		std::ofstream m_file;
	};
}