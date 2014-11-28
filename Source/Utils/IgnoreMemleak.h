#pragma once

#include "DebugOnly.h"

/** Ignore all memory leaks caused by memory allocations within parenthesis. */
#define IGNORE_MEMLEAK(CODE) \
int __flags; \
DEBUG_ONLY(__flags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG); \
_CrtSetDbgFlag(__flags & ~_CRTDBG_ALLOC_MEM_DF);) \
CODE \
DEBUG_ONLY(_CrtSetDbgFlag(__flags);)

