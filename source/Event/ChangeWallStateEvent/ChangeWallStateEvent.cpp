#include "ChangeWallStateEvent.hpp"
#include "../../Map/Map.hpp"

namespace lustro
{
	ChangeWallStateEvent::ChangeWallStateEvent(std::map<std::string, Map>* maps, IniInterpreter::Section* section)
	{
		const std::vector<Wall*>& cont = (*maps)[section->getVariable<std::string>("map")].getWalls();
		for(auto& i : cont)
		{
			if(i->getName() == section->getVariable<std::string>("wall"))
			{
				wall = i;
			}
		}
		state = section->getVariable<bool>("state");
	}
		
	bool ChangeWallStateEvent::run()
	{
		wall->setActivityState(state);
		return true;
	}

}
