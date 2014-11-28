#pragma once

namespace ae
{
	/** Utility class to make various things easier. */
	class Time
	{
	public:
		/** Puts current thread to sleep for specified amount of milliseconds. */
		static void sleep(int ms);
		/** Delay thread with computation, allows higher precision than sleep(). */
		static void busyWait(float ms);
	};
}