#include "../includes/Timer.h"

sushi::Timer::Timer()
{
    this->timerStart = getTimeMicroSec();
    this->counter = 0;
}

sushi::Timer::~Timer()
{
    
}

void sushi::Timer::timerTick()
{
    this->counter++;
}

uint32_t sushi::Timer::getCycleTickMicroSec()
{
    return 0;
}

uint32_t sushi::Timer::getTimeSec()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    return (uint32_t)std::chrono::time_point_cast<std::chrono::seconds>(now).time_since_epoch().count();
}

uint32_t sushi::Timer::getTimeMiliSec()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    return (uint32_t)std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count();
}

uint32_t sushi::Timer::getTimeMicroSec()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    return (uint32_t)std::chrono::time_point_cast<std::chrono::microseconds>(now).time_since_epoch().count();
}
