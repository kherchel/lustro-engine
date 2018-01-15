#include "../Drawable.hpp"

#ifndef POPUP_HPP
#define POPUP_HPP

namespace lustro
{

	class Popup : public Drawable
	{
		public:
			Popup();
			//Popup(unsigned int, unsigned int, unsigned int, unsigned int, std::string, PixelData);
			
			void setText(std::string);
			void setColor(PixelData);
			void setTextPosition(unsigned int);
			void setBorderSize(unsigned int);
			void update();
			void render();
		private:
			PixelData color;
			std::string text;
			unsigned int lines;
			unsigned int borderSize;
			unsigned int textPosition;
			/*
				0 - center (default)
				1 - top
				2 - top right
				3 - right
				4 - bottom right
				5 - bottom
				6 - bottom left
				7 - left
				8 - top left
			*/
			
	};
}

#endif
