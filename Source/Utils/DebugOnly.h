#pragma once

#ifdef _DEBUG
/** Make sure code is only run in debug. */
#define DEBUG_ONLY(CODE) CODE
#else
#define DEBUG_ONLY(CODE) 
#endif

#ifdef _DEBUG
/** Make sure code is only run in release. */
#define RELEASE_ONLY(CODE) 
#else
#define RELEASE_ONLY(CODE) CODE
#endif