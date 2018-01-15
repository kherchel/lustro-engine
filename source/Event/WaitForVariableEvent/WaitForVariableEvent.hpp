#include "../Event.hpp"
#include "../../IniInterpreter/Section.hpp"

#ifndef WAITFORVARIABLEEVENT_HPP
#define WAITFORVARIABLEEVENT_HPP

namespace lustro
{
	
	class WaitForVariableEvent : public Event
	{
	public:
		WaitForVariableEvent(IniInterpreter::Section* section);
		bool run() override;
			
	protected:
		std::string name, value;
	};

}

#endif
