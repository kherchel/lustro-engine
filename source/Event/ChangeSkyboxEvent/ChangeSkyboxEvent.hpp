#include "../../Texture/Texture.hpp"
#include "../Event.hpp"
#include "../../IniInterpreter/Section.hpp"

#include <map>

#ifndef CHANGESKYBOXEVENT_HPP
#define CHANGESKYBOXEVENT_HPP

namespace lustro
{

	class Map;
	
	class ChangeSkyboxEvent : public Event
	{
	public:
		ChangeSkyboxEvent(std::map<std::string, Map>* maps, std::map<std::string, Texture>* textures, IniInterpreter::Section* section);
		bool run() override;
			
	protected:
		Map* map;
		Texture* texture;
	};

}

#endif
