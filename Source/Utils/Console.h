#pragma once

#include "StringConvert.h"
#include "Output.h"

#include <iostream> // ostream, cout

namespace ae
{
	/** Makes writing console applications more convenient. */
	class Console
	{
	public:
		#pragma region NestedClasses
		class _Write
		{
		public:
			template<class T>
			_Write& operator<<(const T& in);
			_Write& operator<<(bool in);
		};

		class _Write_CheckCopies : public _Write
		{
		public:
			_Write_CheckCopies();
			_Write_CheckCopies(_Write_CheckCopies& other);
			_Write_CheckCopies& operator=(_Write_CheckCopies& other);
			bool isCopied() const;

		private:
			bool m_copied;
		};

		class _PrintLn : public _Write_CheckCopies
		{
		public:
			~_PrintLn();
		};

		class _Write_CheckLenght : public _Write_CheckCopies
		{
		public:
			_Write_CheckLenght();
			template <class T>
			_Write_CheckLenght& operator<<(const T& in);
			int lenght() const;

		private:
			int m_lenght;
		};

		class _PrintTitle : public _Write_CheckLenght
		{
		public:
			~_PrintTitle();
		};

		class _PrintSubtitle : public _Write_CheckLenght
		{
		public:
			~_PrintSubtitle();
		};
		#pragma endregion

		/** Pauses execution until a key is pressed. */
		static void pressToContinue();
		/** Writes input added using the input stream operator. E.g.
			Console::write() << "Hello World"; */
		static _Write write();
		/** Same as write(), but ends output with a newline. */
		static _PrintLn print();
		/** Same as print(), but also underlines the printed text. */
		static _PrintTitle printTitle();
		/** Same as printTitle(), but uses a smaller underline. */
		static _PrintSubtitle printSubtitle();
		/** Changes text color in console, where color is a value between 0-15.
			Only supports Windows currently. */
		static void setColor(int color);
		/** Changes text background color in console, where color is a value
			between 0-15. Only supports Windows currently. */
		static void setBackground(int color);
		/** Restores any change in console color to default. */
		static void restoreDefaultColors();
	};

	template<class T>
	Console::_Write& Console::_Write::operator<<(const T& in)
	{
		std::cout << in;

		return *this;
	}

	template<class T>
	Console::_Write_CheckLenght& Console::_Write_CheckLenght::operator<<(const T& in)
	{
		std::string text = StringConvert::toString(in);
		m_lenght += (int)text.length();

		std::cout << text;

		return *this;
	}
}

