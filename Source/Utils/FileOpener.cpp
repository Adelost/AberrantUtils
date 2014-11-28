#include "FileOpener.h"

namespace ae
{
	FileOpener::FileOpener(const char* path)
	{
		m_file.open(path);
	}

	FileOpener::~FileOpener()
	{
		m_file.close();
	}

	void FileOpener::write(std::string text)
	{
		if (m_file.is_open())
		{
			m_file << text.c_str();
		}
	}
}