#include "../../Event/Event.hpp"
#include "../Object.hpp"
#include <vector>
#include <map>
#include <string>
#ifndef EVENTCONTAINER_HPP
#define EVENTCONTAINER_HPP

namespace lustro
{

	class EventContainer : public Object
	{
		public:
			EventContainer();
			EventContainer(std::string name, double x, double y, bool isActive, Animation animation);
			~EventContainer();
			void setMode(std::string group, std::string mode);
			void addEvent(Event* event, std::string group, unsigned int list = 0);
		protected:
			typedef std::vector<Event*> EventList;
			struct EventGroup
			{
				std::vector<EventList> events;
				std::string mode;               //possible modes: "once", "multiple"
				unsigned int current;
			};
			
			std::map<std::string, EventGroup> eventGroups;
			
			void runEvents(std::string);
	};

}

#endif
