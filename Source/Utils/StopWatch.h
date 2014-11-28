#pragma once

#include <string>

namespace ae
{
	/** High-precision time measuring class, useful when profiling code. The timer
		starts automatically during initialization, but may also be started using
		start(). */
	class StopWatch
	{
	public:
		StopWatch();

		/** Resets any accumulated time and starts the timer. */
		void start();
		/** Pauses the timer. */
		void pause();
		/** Resumes the timer from a paused state. */
		void resume();

		/** Prints elapsed time in milliseconds to console. */
		void printTime();
		/** Prints elapsed time in milliseconds to console. */
		void printTime(std::string label);

		/** Returns elapsed time in seconds. */
		float time();
		/** Returns elapsed time in whole milliseconds. */
		int timeMs();
		/** Returns elapsed time in milliseconds. */
		float timeMsFloat();
		/** Returns elapsed time in nanoseconds to console. */
		int timeNano();
		/** Returns time since last pause. */
		float pausedTime();
		/** Returns true if the timer is currently paused. */
		bool isPaused();

	private:
		__int64 cpuTime();
		__int64 cpuPauseTime();

		__int64 m_cpuTime;
		__int64 m_cpuPause;
		bool m_paused;
	};
}