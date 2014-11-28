#pragma once

/** Custom assert macros. More safe than standard assert, and a prints a nicer
	call stack.

	Credits goes to this article by Charles Nicholson:
	http://cnicholson.net/2009/02/stupid-c-tricks-adventures-in-assert/ */


#ifdef _DEBUG
#define _XASSERTS_ENABLED // Uncomment this line to silence all xassert
#endif

namespace XAssert
{
	enum FailBehavior
	{
		BREAK,
		CONTINUE
	};

	// Run every time an assert fails
	int onFailure(const char* condition, const char* file, int line,
	              const char* msg, ...);
}

// Halts execution of the program
#define _XASSERT_HALT() __debugbreak()
// This code is run in release mode. Will be optimized away in GCC and MSVC
#define _XASSERT_UNUSED(x) do {(void)sizeof(x);} while(0)

#ifdef _XASSERTS_ENABLED

// Assert macro
#define xassert(cond) \
	do \
		{ \
		if (!(cond)) \
				{ \
			if (XAssert::onFailure(#cond, __FILE__, __LINE__, 0) == \
			XAssert::BREAK) \
			_XASSERT_HALT(); \
				} \
		} while(0)

// Assert macro with message printing
#define xassert_msg(cond, msg, ...) \
	do \
		{ \
		if (!(cond)) \
				{ \
			if (XAssert::onFailure(#cond, __FILE__, __LINE__, (msg), __VA_ARGS__) == \
			XAssert::BREAK) \
			_XASSERT_HALT(); \
				} \
		} while(0)
#else

#define xassert(condition) \
	do {_XASSERT_UNUSED(condition);} while(0)
#define xassert_msg(condition, msg, ...) \
	do {_XASSERT_UNUSED(condition); _XASSERT_UNUSED(msg);} while(0)

#endif

