#include "ChangeTextureEvent.hpp"
#include "../../Map/Map.hpp"

namespace lustro
{
	ChangeTextureEvent::ChangeTextureEvent(std::map<std::string, Map>* maps, std::map<std::string, Texture>* textures, IniInterpreter::Section* section)
	{
		const std::vector<Wall*>& cont = (*maps)[section->getVariable<std::string>("map")].getWalls();
		for(auto& i : cont)
		{
			if(i->getName() == section->getVariable<std::string>("wall"))
			{
				wall = i;
			}
		}
		texture = &((*textures)[section->getVariable<std::string>("texture")]);	
	}
		
	bool ChangeTextureEvent::run()
	{
		wall->setTexture(texture);
		return true;
	}

}
