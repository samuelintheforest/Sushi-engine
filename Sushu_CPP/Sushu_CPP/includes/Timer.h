#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>


namespace sushi
{
	class Timer
	{
	public:
		Timer();
		~Timer();
		void timerTick();
		uint64_t getCycleTickMicroSec();
		uint64_t getTimeSec();
		uint64_t getTimeMiliSec();
		uint64_t getTimeMicroSec();
	
	private:
		std::chrono::time_point<std::chrono::steady_clock> timerStartus;
		uint64_t counter;
	};
}

#endif
