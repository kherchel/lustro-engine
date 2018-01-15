#include "ChangeSkyboxEvent.hpp"
#include "../../Map/Map.hpp"

namespace lustro
{
	ChangeSkyboxEvent::ChangeSkyboxEvent(std::map<std::string, Map>* maps, std::map<std::string, Texture>* textures, IniInterpreter::Section* section)
	{
		map = &((*maps)[section->getVariable<std::string>("map")]);
		texture = &((*textures)[section->getVariable<std::string>("texture")]);	
	}
		
	bool ChangeSkyboxEvent::run()
	{
		map->getSkybox()->bindTexture(texture);
		return true;
	}

}
