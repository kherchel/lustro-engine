#include "../Event.hpp"
#include "../../Inventory/Inventory.hpp"
#include "../../IniInterpreter/Section.hpp"

#ifndef ADDITEMEVENT_HPP
#define ADDITEMEVENT_HPP

namespace lustro
{
	
	class AddItemEvent : public Event
	{
	public:
		AddItemEvent(IniInterpreter::Section* section);
		bool run() override;
			
	protected:
		std::string name, description;
	};

}

#endif
