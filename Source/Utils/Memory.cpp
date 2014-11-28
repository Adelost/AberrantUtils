#include "Memory.h"

#include "DebugOnly.h"

#include <cstring> // memcpy, memmove
#include <crtdbg.h> // _CrtSetDbgFlag

namespace ae
{
	void Memory::copyRaw(const void* source, void* destination, int bytes)
	{
		memcpy(destination, source, bytes);
	}

	void Memory::moveRaw(const void* source, void* destination, int bytes)
	{
		memmove(destination, source, bytes);
	}

	void Memory::enableLeakDetection()
	{
		DEBUG_ONLY(_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);)
	}

	void Memory::deallocateRaw(void* data)
	{
		delete[] data;
	}
}
