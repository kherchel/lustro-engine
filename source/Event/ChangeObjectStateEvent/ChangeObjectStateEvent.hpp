#include "../../Object/Object.hpp"
#include "../Event.hpp"
#include "../../IniInterpreter/Section.hpp"

#include <map>

#ifndef CHANGEOBJECTSTATEEVENT_HPP
#define CHANGEOBJECTSTATEEVENT_HPP

namespace lustro
{

	class Map;
	
	class ChangeObjectStateEvent : public Event
	{
	public:
		ChangeObjectStateEvent(std::map<std::string, Map>* maps, IniInterpreter::Section* section);
		bool run() override;
			
	protected:
		Object* object;
		bool state;
	};

}

#endif
