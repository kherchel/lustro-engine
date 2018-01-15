#include "ChangeObjectStateEvent.hpp"
#include "../../Map/Map.hpp"

namespace lustro
{
	ChangeObjectStateEvent::ChangeObjectStateEvent(std::map<std::string, Map>* maps, IniInterpreter::Section* section)
	{
		const std::vector<Object*>& cont = (*maps)[section->getVariable<std::string>("map")].getObjects();
		for(auto& i : cont)
		{
			if(i->getName() == section->getVariable<std::string>("object"))
			{
				object = i;
			}
		}
		const std::vector<EventContainer*>& contw = (*maps)[section->getVariable<std::string>("map")].getEventContainers();
		for(auto& i : contw)
		{
			if(i->getName() == section->getVariable<std::string>("object"))
			{
				object = i;
			}
		}
		state = section->getVariable<bool>("state");
	}
		
	bool ChangeObjectStateEvent::run()
	{
		object->setActivityState(state);
		return true;
	}

}
