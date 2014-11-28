#include "Time.h"

#include <chrono> // sleep_for
#include <iostream>
#include <thread>

#include "StopWatch.h"

namespace ae
{
	void Time::sleep(int ms)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}

	void Time::busyWait(float ms)
	{
		StopWatch timer;
		while (timer.timeMsFloat() < ms)
		{
			// Do nothing
		}
	}
}
