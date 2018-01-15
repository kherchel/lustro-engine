#include "SetVariableEvent.hpp"

namespace lustro
{
	SetVariableEvent::SetVariableEvent(IniInterpreter::Section* section)
	{
		name = section->getVariable<std::string>("name");
		value = section->getVariable<std::string>("value");
	}
		
	bool SetVariableEvent::run()
	{
		setVariable(name, value);
		return true;
	}
}
