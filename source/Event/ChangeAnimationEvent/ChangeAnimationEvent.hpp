#include "../../Object/Object.hpp"
#include "../Event.hpp"
#include "../../IniInterpreter/Section.hpp"

#include <map>

#ifndef CHANGEANIMATIONEVENT_HPP
#define CHANGEANIMATIONEVENT_HPP

namespace lustro
{

	class Map;
	
	class ChangeAnimationEvent : public Event
	{
	public:
		ChangeAnimationEvent(std::map<std::string, Map>* maps, std::map<std::string, Animation>* animations, IniInterpreter::Section* section);
		bool run() override;
			
	protected:
		Object* object;
		Animation animation;
	};

}

#endif
