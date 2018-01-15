#include "EventContainer.hpp"

namespace lustro
{
	EventContainer::EventContainer(){}
	
	EventContainer::EventContainer(std::string name, double x, double y, bool isActive, Animation animation) 
		: Object(name, x, y, isActive, animation) {}
	
	EventContainer::~EventContainer()
	{
		for(auto& i : eventGroups)
			for(auto& j : i.second.events)
				for(auto& g: j)
					delete g;
	}
	
	void EventContainer::addEvent(Event* event, std::string group, unsigned int list)
	{
		if(eventGroups.count(group) == 0) eventGroups[group] = EventGroup();
		while(eventGroups[group].events.size() <= list) 
			eventGroups[group].events.push_back(EventList());
			
		eventGroups[group].events[list].push_back(event);
	}
	
	void EventContainer::setMode(std::string group, std::string mode)
	{
		if(eventGroups.count(group) == 0) eventGroups[group] = EventGroup();
		eventGroups[group].mode = mode;
	}

	void EventContainer::runEvents(std::string group)
	{
		if(eventGroups[group].current < eventGroups[group].events.size())
		{
			bool success = true;
			for(auto& i : eventGroups[group].events[eventGroups[group].current])
				{success = i->run(); if(!success) break;}
		
			if(success)eventGroups[group].current++;
		}

		if(eventGroups[group].current >= eventGroups[group].events.size()
			&& eventGroups[group].mode == "multiple") 
			{eventGroups[group].current = 0;}
		
	}
}
