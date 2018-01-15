#include "DisplayMessageEvent.hpp"
#include "../../Drawable/Toast/Toast.hpp"
#include "../../Drawable/Log/Log.hpp"
namespace lustro
{
	DisplayMessageEvent::DisplayMessageEvent(Toast* toast, Log* log, IniInterpreter::Section* section)
		: toast(toast), log(log)
	{
		message = section->getVariable<std::string>("message");
	}
		
	bool DisplayMessageEvent::run()
	{
		toast->start(message);
		log->addMessage(message);
		return true;
	}
}
