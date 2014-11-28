#pragma once

/** Allows code to be called automatically during the start of the program. Only
    to be used in .cpp files. Be sure to watch out for "static initialization
    order fiasco", http://www.parashift.com/c++-faq/static-init-order.html. */
#define STATIC_CALL(CODE) \
namespace \
{ \
	class _StaticCall \
	{ \
	public: \
		_StaticCall() \
		{ \
			CODE \
		} \
	}; \
	_StaticCall _staticCall; \
}