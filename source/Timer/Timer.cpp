#include "Timer.hpp"

namespace lustro
{
	Timer::Timer()
	{
		last = 0;
	}
	
	void Timer::start()
	{
		last = 0;
		gettimeofday(&startT, NULL);
	}
	
	void Timer::stop()
	{
		gettimeofday(&endT, NULL);
		last = (endT.tv_sec - startT.tv_sec)*1000 + (endT.tv_usec - startT.tv_usec)/1000.;
	}
	
	void Timer::next()
	{
		stop();
		gettimeofday(&startT, NULL);
	}
	
	double Timer::getMillis()
	{
		return last;
	}
	
	double Timer::getSeconds()
	{
		return last/1000.;
	}
	
	double Timer::getMinutes()
	{
		return last/1000./60.;
	}
}
