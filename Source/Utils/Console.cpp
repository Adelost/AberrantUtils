#include "Console.h"

#include "_WindowsConsole.h"

namespace ae
{
	void Console::pressToContinue()
	{
		std::cout << "\n\nPress any key to continue . . .";
		std::cin.ignore();
		std::cout << "\n\n";
	}

	Console::_Write Console::write()
	{
		return _Write();
	}

	Console::_PrintLn Console::print()
	{
		return _PrintLn();
	}

	Console::_PrintTitle Console::printTitle()
	{
		return _PrintTitle();
	}

	Console::_PrintSubtitle Console::printSubtitle()
	{
		return _PrintSubtitle();
	}

	void Console::setColor(int color)
	{
		_WindowsConsole::setColor(color);
	}

	void Console::setBackground(int color)
	{
		_WindowsConsole::setBackground(color);
	}

	void Console::restoreDefaultColors()
	{
		_WindowsConsole::setColor(7);
		_WindowsConsole::setBackground(0);
	}

	Console::_Write_CheckCopies::_Write_CheckCopies()
	{
		m_copied = false;
	}

	Console::_Write_CheckCopies::_Write_CheckCopies(Console::_Write_CheckCopies& other) : _Write_CheckCopies()
	{
		*this = other;
	}

	Console::_Write_CheckCopies& Console::_Write_CheckCopies::operator=(Console::_Write_CheckCopies& other)
	{
		// Normally return value optimization prevents the class from being copied, but
		// if not, we have to keep track of copies
		other.m_copied = true;

		return *this;
	}

	bool Console::_Write_CheckCopies::isCopied() const
	{
		return m_copied;
	}

	Console::_PrintLn::~_PrintLn()
	{
		if (!isCopied())
			std::cout << "\n";
	}

	Console::_Write_CheckLenght::_Write_CheckLenght()
	{
		m_lenght = 0;
	}

	int Console::_Write_CheckLenght::lenght() const
	{
		return m_lenght;
	}

	Console::_PrintTitle::~_PrintTitle()
	{
		if (!isCopied())
		{
			std::cout << "\n";
			for (int i = 0; i < lenght(); i++)
				std::cout << "=";
			std::cout << "\n";
		}
	}

	Console::_PrintSubtitle::~_PrintSubtitle()
	{
		if (!isCopied())
		{
			std::cout << "\n";
			for (int i = 0; i < lenght(); i++)
				std::cout << "-";
			std::cout << "\n";
		}
	}

	Console::_Write& Console::_Write::operator<<(bool in)
	{
		return *this << StringConvert::toString(in);
	}
}