#include "../../Wall/Wall.hpp"
#include "../Event.hpp"
#include "../../IniInterpreter/Section.hpp"

#include <map>

#ifndef CHANGEWALLSTATEEVENT_HPP
#define CHANGEWALLSTATEEVENT_HPP

namespace lustro
{

	class Map;
	
	class ChangeWallStateEvent : public Event
	{
	public:
		ChangeWallStateEvent(std::map<std::string, Map>* maps, IniInterpreter::Section* section);
		bool run() override;
			
	protected:
		Wall* wall;
		bool state;
	};

}

#endif
