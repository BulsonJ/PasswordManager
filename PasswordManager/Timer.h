#pragma once
#include <chrono>
class Timer
{
public:
	Timer() {};
	~Timer() {};
	void start();
	void stop();
	double elapsedTime();
protected:
	std::chrono::time_point<std::chrono::system_clock> start_time;
	std::chrono::time_point<std::chrono::system_clock> end_time;
	bool running = false;
};

