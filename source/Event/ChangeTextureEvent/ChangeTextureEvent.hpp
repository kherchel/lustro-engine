#include "../../Wall/Wall.hpp"
#include "../Event.hpp"
#include "../../IniInterpreter/Section.hpp"

#include <map>

#ifndef CHANGETEXTUREEVENT_HPP
#define CHANGETEXTUREEVENT_HPP

namespace lustro
{

	class Map;
	
	class ChangeTextureEvent : public Event
	{
	public:
		ChangeTextureEvent(std::map<std::string, Map>* maps, std::map<std::string, Texture>* textures, IniInterpreter::Section* section);
		bool run() override;
			
	protected:
		Wall* wall;
		Texture* texture;
	};

}

#endif
