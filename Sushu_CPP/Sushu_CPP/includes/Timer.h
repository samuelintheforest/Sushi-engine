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
		uint32_t getCycleTickMicroSec();
		uint32_t getTimeSec();
		uint32_t getTimeMiliSec();
		uint32_t getTimeMicroSec();
	
	private:
		uint32_t timerStart;
		uint32_t counter;
	};
}

#endif
