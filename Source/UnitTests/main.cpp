#include <Utils/Console.h>
#include <Utils/Memory.h>

#include "Tests.h"



#define CATCH_CONFIG_RUNNER
#include <Catch/include/catch.hpp>

#include <Utils/Array.h>
using namespace ae;

int main()
{
	Memory::enableLeakDetection();

	Array<int> foo;

	Catch::Session().run();

	Console::pressToContinue();

	return 0;
}


