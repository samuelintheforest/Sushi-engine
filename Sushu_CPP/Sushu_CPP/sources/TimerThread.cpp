#include "../includes/TimerThread.h"

uint64_t sushi::TimerThread::counter;
uint8_t sushi::TimerThread::flag;
std::thread* sushi::TimerThread::timerThread;

void sushi::TimerThread::initThread()
{
	sushi::TimerThread::flag = 1;
	sushi::TimerThread::counter = 0;
	sushi::TimerThread::timerThread = new std::thread(tickProgram);
}

void sushi::TimerThread::destroyThread()
{
	sushi::TimerThread::flag = 0;
	sushi::TimerThread::timerThread->join();
	std::cout << "TimerThread counting stopped!" << "\n";
	
	delete sushi::TimerThread::timerThread;
}

uint64_t sushi::TimerThread::getTickMicro()
{
	return 0;
}

void sushi::TimerThread::tickProgram()
{

}