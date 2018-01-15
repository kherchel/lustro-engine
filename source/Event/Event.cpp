#include "Event.hpp"

namespace lustro
{
	std::map<std::string, std::string> Event::variables;
	
	bool Event::isVariable(std::string name)
	{
		return variables.count(name);
	}
	
	std::string Event::getVariable(std::string name)
	{
		if(!isVariable(name)) return "";
		return variables[name];
	}
	
	void Event::setVariable(std::string name, std::string value) 
	{
		variables[name] = value;
	}
}
