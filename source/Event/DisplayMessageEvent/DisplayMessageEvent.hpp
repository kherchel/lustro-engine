#include "../Event.hpp"
#include "../../IniInterpreter/Section.hpp"

#ifndef DISPLAYMESSAGEEVENT_HPP
#define DISPLAYMESSAGEEVENT_HPP

namespace lustro
{
	class Toast;
	class Log;

	class DisplayMessageEvent : public Event
	{
	public:
		DisplayMessageEvent(Toast* toast, Log* log, IniInterpreter::Section* section);
		bool run() override;
			
	protected:
		std::string message;
		Toast* toast;
		Log* log;
	};

}

#endif
