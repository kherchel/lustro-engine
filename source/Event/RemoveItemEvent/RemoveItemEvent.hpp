#include "../Event.hpp"
#include "../../Inventory/Inventory.hpp"
#include "../../IniInterpreter/Section.hpp"

#ifndef REMOVEITEMEVENT_HPP
#define REMOVEITEMEVENT_HPP

namespace lustro
{
	
	class RemoveItemEvent : public Event
	{
	public:
		RemoveItemEvent(IniInterpreter::Section* section);
		bool run() override;
			
	protected:
		std::string name;
	};

}

#endif
