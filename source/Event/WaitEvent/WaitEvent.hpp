#include "../../Timer/Timer.hpp"
#include "../Event.hpp"
#include "../../IniInterpreter/Section.hpp"

#ifndef WAITEVENT_HPP
#define WAITEVENT_HPP

namespace lustro
{
	
	class WaitEvent : public Event
	{
	public:
		WaitEvent(IniInterpreter::Section* section);
		bool run() override;
			
	protected:
		std::string timerName;
		double time;
		bool started;
	};

}

#endif
