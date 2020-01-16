#include "Clock.h"

Clock::Clock() : 
	mTime(0.0)
{
	mPoint = std::chrono::high_resolution_clock::now();
}

void Clock::Reset()
{
	mPoint = std::chrono::high_resolution_clock::now();
}

void Clock::Step()
{
	const std::chrono::duration<float> dt = std::chrono::high_resolution_clock::now() - mPoint;

	mTime += dt.count();
}

double Clock::GetTime()
{
	return mTime;
}
