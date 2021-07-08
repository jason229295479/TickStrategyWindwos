#ifndef _TIMER_H_
#define _TIMER_H


#include <chrono>

class Timer
{
public:
	Timer();

	void Reset();

	//ƒ¨»œ∫¡√Î
	template<typename Duration = std::chrono::milliseconds>
	int64_t Elapsedmill() const
	{
		return std::chrono::duration_cast<Duration>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}

	int64_t ElapsedMicro() const; // Œ¢√Î
	int64_t ElapsedNano() const; //ƒ…√Î
	int64_t ElapsedSeconds() const; //√Î
	int64_t ElapsedMinutes() const; //∑÷
	int64_t ElapsedHours() const; // ±
	

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
};


#endif // _TIMER_H_
