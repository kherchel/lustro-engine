#include "../IniInterpreter/Section.hpp"

#ifndef EVENT_HPP
#define EVENT_HPP

namespace lustro
{
	class Event
	{
		public:
			virtual bool run() = 0;
		
		protected:
			static bool isVariable(std::string);
			static std::string getVariable(std::string);
			static void setVariable(std::string, std::string);
		private:
			static std::map<std::string, std::string> variables;
	};
}

#endif
