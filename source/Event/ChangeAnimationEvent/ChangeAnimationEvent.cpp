#include "ChangeAnimationEvent.hpp"
#include "../../Map/Map.hpp"

namespace lustro
{
	ChangeAnimationEvent::ChangeAnimationEvent(std::map<std::string, Map>* maps, std::map<std::string, Animation>* animations, IniInterpreter::Section* section)
	{
		const std::vector<Object*>& cont = (*maps)[section->getVariable<std::string>("map")].getObjects();
		for(auto& i : cont)
		{
			if(i->getName() == section->getVariable<std::string>("object"))
			{
				object = i;
			}
		}
		animation = (*animations)[section->getVariable<std::string>("animation")];	
	}
		
	bool ChangeAnimationEvent::run()
	{
		object->setAnimation(animation);
		return true;
	}

}
