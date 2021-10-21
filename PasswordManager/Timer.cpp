#include "Timer.h"

void Timer::start() {
	start_time = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
	end_time = std::chrono::high_resolution_clock::now();
}