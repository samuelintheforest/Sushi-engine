#include "Timer.h"

sushi::Timer::Timer()
{
    this->timerStartus = std::chrono::steady_clock::now();
    this->counter = 0;
}

sushi::Timer::~Timer()
{
    
}

void sushi::Timer::timerTick()
{
    this->counter++;
}

uint64_t sushi::Timer::getCycleTickMicroSec()
{
    return 0;
}

uint64_t sushi::Timer::getTimeSec()
{
    return (uint64_t)std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - timerStartus).count();
}

uint64_t sushi::Timer::getTimeMiliSec()
{
    return (uint64_t)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timerStartus).count();
}

uint64_t sushi::Timer::getTimeMicroSec()
{
    return (uint64_t)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - timerStartus).count();
}
