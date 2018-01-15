#include "LinkWallEvent.hpp"
#include "../../Map/Map.hpp"

namespace lustro
{
	LinkWallEvent::LinkWallEvent(std::map<std::string, Map>* maps, IniInterpreter::Section* section)
		: map1(nullptr), map2(nullptr), wall1(nullptr), wall2(nullptr)
	{
		if((*maps).count(section->getVariable<std::string>("map1")) != 0)
		{
			map1 = &(*maps)[section->getVariable<std::string>("map1")];
			const std::vector<Wall*>& cont1 = map1->getWalls();
			for(auto& i : cont1)
			{
				if(i->getName() == section->getVariable<std::string>("wall1"))
				{
					wall1 = (LinkedWall*)i;
				}
			}
		}	
		if((*maps).count(section->getVariable<std::string>("map2")) != 0)
		{
			map2 = &(*maps)[section->getVariable<std::string>("map2")];
			const std::vector<Wall*>& cont2 = map2->getWalls();
			for(auto& i : cont2)
			{
				if(i->getName() == section->getVariable<std::string>("wall2"))
				{
					wall2 = (LinkedWall*)i;
				}
			}
		}
		doublyLinked = !(section->isVariable("doublyLinked")) || (section->getVariable<bool>("doublyLinked"));
	}
		
	bool LinkWallEvent::run()
	{
		if(wall1 == nullptr || wall2 == nullptr || map1 == nullptr || map2 == nullptr) return false;
		if(doublyLinked)
			wall2->link(map1, wall1);
		
		wall1->link(map2, wall2);
		return true;
	}

}
