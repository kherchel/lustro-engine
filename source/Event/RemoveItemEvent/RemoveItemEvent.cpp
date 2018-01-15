#include "RemoveItemEvent.hpp"

namespace lustro
{
	RemoveItemEvent::RemoveItemEvent(IniInterpreter::Section* section)
	{
		name = section->getVariable<std::string>("name");
	}
		
	bool RemoveItemEvent::run()
	{
		Inventory::removeItem(name);
	}

}
