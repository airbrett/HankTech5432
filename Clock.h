#pragma once
#include <chrono>

class Clock
{
private:
	double mTime;
	double mDT;
	std::chrono::time_point<std::chrono::high_resolution_clock> mPoint;

public:
	Clock();

	void Reset();
	void Step();
	double GetTime();
	double GetDT();
};
