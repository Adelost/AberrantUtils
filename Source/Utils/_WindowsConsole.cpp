#include "_WindowsConsole.h"

#include "windows.h"

namespace ae
{
	namespace
	{
		int s_currentColor = 0;
		int s_currentBackground = 0;

		void updateConsole()
		{
			HANDLE handle;
			handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(handle, s_currentColor + s_currentBackground * 16);
		}
	}

	void _WindowsConsole::setColor(int color)
	{
		s_currentColor = color % 16;
		updateConsole();
	}

	void _WindowsConsole::setBackground(int color)
	{
		s_currentBackground = color % 16;
		updateConsole();
	}
}