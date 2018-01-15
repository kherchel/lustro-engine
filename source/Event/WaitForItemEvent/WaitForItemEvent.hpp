#include "../Event.hpp"
#include "../../Inventory/Inventory.hpp"
#include "../../IniInterpreter/Section.hpp"

#ifndef WAITFORITEMEVENT_HPP
#define WAITFORITEMEVENT_HPP

namespace lustro
{
	
	class WaitForItemEvent : public Event
	{
	public:
		WaitForItemEvent(IniInterpreter::Section* section);
		bool run() override;
			
	protected:
		std::string name;
	};

}

#endif
