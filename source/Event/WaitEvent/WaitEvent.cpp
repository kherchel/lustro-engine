#include "WaitEvent.hpp"

namespace lustro
{
	WaitEvent::WaitEvent(IniInterpreter::Section* section)
	{
		timerName = section->getVariable<std::string>("timerName");
		time = section->getVariable<double>("time");
		started = false;
	}
		
	bool WaitEvent::run()
	{
		if(!started)
		{
			Timer::start(timerName);
			started = true;
			return false;
		}
		Timer::stop(timerName);
		if(time <= Timer::getSeconds(timerName))
		{
			started = false;
			return true;
		}
		return false;
	}

}
