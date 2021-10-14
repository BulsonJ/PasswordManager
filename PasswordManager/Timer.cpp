#include "Timer.h"

void Timer::start() {
	start_time = std::chrono::system_clock::now();
}

void Timer::stop() {
	end_time = std::chrono::system_clock::now();
}

double Timer::elapsedTime() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
}