#pragma once

/** Make sure code in input parameter is only run once. */
#define CALL_ONCE(CODE) \
{ \
	static bool first = true; \
	if(first) \
	{ \
		first = false; \
		CODE\
	} \
}