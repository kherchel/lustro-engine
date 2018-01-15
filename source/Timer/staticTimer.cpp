#include "Timer.hpp"

#ifndef STATICTIMER_CPP
#define STATICTIMER_CPP



namespace lustro
{
	std::map<std::string, Timer> Timer::timers;


	void Timer::start(std::string name)
	{
		timers[name].start();
	}
	
	void Timer::stop(std::string name)
	{
		timers[name].stop();
	}
	
	void Timer::next(std::string name)
	{
		timers[name].next();
	}
	
	float Timer::getMillis(std::string name)
	{
		return timers[name].getMillis();
	}
	
	float Timer::getSeconds(std::string name)
	{
		return timers[name].getSeconds();
	}
	
	float Timer::getMinutes(std::string name)
	{
		return timers[name].getMinutes();
	}

}

#endif
