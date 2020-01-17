#include "Clock.h"

Clock::Clock() : 
	mTime(0.0)
{
	Reset();
}

void Clock::Reset()
{
	mPoint = std::chrono::high_resolution_clock::now();
}

void Clock::Step()
{
	const std::chrono::time_point<std::chrono::high_resolution_clock> Now = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<float> dt = Now - mPoint;

	mTime += dt.count();

	mPoint = Now;
}

double Clock::GetTime()
{
	return mTime;
}
