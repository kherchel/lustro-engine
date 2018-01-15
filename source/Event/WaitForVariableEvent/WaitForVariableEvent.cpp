#include "WaitForVariableEvent.hpp"

namespace lustro
{
	WaitForVariableEvent::WaitForVariableEvent(IniInterpreter::Section* section)
	{
		name = section->getVariable<std::string>("name");
		value = section->getVariable<std::string>("value");
	}
		
	bool WaitForVariableEvent::run()
	{
		return getVariable(name) == value;
	}

}
