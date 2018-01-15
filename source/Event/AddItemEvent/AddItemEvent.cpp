#include "AddItemEvent.hpp"

namespace lustro
{
	AddItemEvent::AddItemEvent(IniInterpreter::Section* section)
	{
		name = section->getVariable<std::string>("name");
		description = section->getVariable<std::string>("description");
	}
		
	bool AddItemEvent::run()
	{
		Inventory::addItem(name, description);
		return true;
	}

}
