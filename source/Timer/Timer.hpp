#include <sys/types.h>
#include <sys/time.h>
#include <map>
#include <string>

#ifndef TIMER_HPP
#define TIMER_HPP

namespace lustro
{
	
	class Timer
	{
		public:
			Timer();
			static void start(std::string name);
			static void stop(std::string name);
			static void next(std::string name);
			static float getMillis(std::string name);
			static float getSeconds(std::string name);
			static float getMinutes(std::string name);
			
			
			static constexpr float appFramerate = 20;
		
		private:
			timeval startT, endT;
			double last;
			
			void start();
			void stop();
			void next();
			double getMillis();
			double getSeconds();
			double getMinutes();
			
			static std::map<std::string, Timer> timers;
	};

}

//#include "staticTimer.cpp"

#endif
