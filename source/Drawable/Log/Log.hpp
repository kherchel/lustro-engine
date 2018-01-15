#include "../Drawable.hpp"

#ifndef LOG_HPP
#define LOG_HPP

namespace lustro
{

	class Log : public Drawable
	{
		public:
			Log();
			Log(PixelData color);
			
			void addMessage(std::string newMessage);
			void update();
			void render();
		private:
			PixelData color;
			std::vector<std::string> messages;
	};
}

#endif
