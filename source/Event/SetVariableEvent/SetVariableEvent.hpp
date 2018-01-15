#include "../Event.hpp"
#include "../../IniInterpreter/Section.hpp"

#ifndef SETVARIABLEEVENT_HPP
#define SETVARIABLEEVENT_HPP

namespace lustro
{

	class SetVariableEvent : public Event
	{
	public:
		SetVariableEvent(IniInterpreter::Section* section);
		bool run() override;
			
	protected:
		std::string name, value;
	};

}

#endif
