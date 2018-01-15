#include "../../Wall/LinkedWall/LinkedWall.hpp"
#include "../Event.hpp"
#include "../../IniInterpreter/Section.hpp"

#include <map>

#ifndef LINKWALLEVENT_HPP
#define LINKWALLEVENT_HPP

namespace lustro
{

	class Map;
	
	class LinkWallEvent : public Event
	{
	public:
		LinkWallEvent(std::map<std::string, Map>* maps, IniInterpreter::Section* section);
		bool run() override;
			
	protected:
		LinkedWall* wall1,* wall2;
		Map* map1,* map2;
		bool doublyLinked;
	};

}

#endif
