#include "Timer.h"


Timer::Timer()
	:m_begin(std::chrono::high_resolution_clock::now())
{

}

void Timer::Reset()
{
	m_begin = std::chrono::high_resolution_clock::now();
}

int64_t Timer::ElapsedMicro() const
{
	return Elapsedmill<std::chrono::microseconds>();
}

int64_t Timer::ElapsedNano() const
{
	return Elapsedmill<std::chrono::nanoseconds>();
}

int64_t Timer::ElapsedSeconds() const
{
	return Elapsedmill<std::chrono::seconds>();
}

int64_t Timer::ElapsedMinutes() const
{
	return Elapsedmill<std::chrono::minutes>();
}

int64_t Timer::ElapsedHours() const
{
	return Elapsedmill<std::chrono::hours>();
}
