#ifndef TIMER_THREAD_H
#define TIMER_THREAD_H

#include <thread>
#include <chrono>
#include <iostream>

namespace sushi
{
	class TimerThread
	{
	public:
		static void initThread();
		static void destroyThread();
		static uint64_t getTickMicro();
		static void tickProgram();

	private:
		static uint64_t counter;
		static std::thread* timerThread;
		static uint8_t flag;
	};
}

#endif
