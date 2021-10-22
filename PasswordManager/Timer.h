#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
public:
	Timer() {};
	~Timer() {};
	void start();
	void stop();
	double elapsedTime() { return std::chrono::duration<double, std::milli>(end_time - start_time).count(); };
protected:
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
	std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
};

#endif

