#include "WaitForItemEvent.hpp"

namespace lustro
{
	WaitForItemEvent::WaitForItemEvent(IniInterpreter::Section* section)
	{
		name = section->getVariable<std::string>("name");
	}
		
	bool WaitForItemEvent::run()
	{
		return Inventory::getCurrentItem().first == name;
	}
}
