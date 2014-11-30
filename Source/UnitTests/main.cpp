#include "Catch.h"
#include "TestUtils.h"

#include <Utils/Console.h>
#include <Utils/Memory.h>

using namespace ae;

int main()
{
	Memory::enableLeakDetection();

	Catch::Session().run();

	Console::pressToContinue();

	return 0;
}


