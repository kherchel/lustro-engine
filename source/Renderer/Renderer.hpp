#ifndef RENDERER_HPP_INCLUDED
#define RENDERER_HPP_INCLUDED

#include <locale.h>
#include <ncurses.h>
#include <unistd.h>
#include <map>
#include <vector>
#include <algorithm>

#include "../PixelData/PixelData.hpp"
#include "../Drawable/Drawable.hpp"
namespace lustro
{
	class Renderer
	{
		public:
			Renderer();
			Renderer(unsigned int, unsigned int);
		
			void bindDrawable(Drawable*, std::string);
			/* ^ Can be a Raycaster, a Spritecaster or a UserInterfaceElement. */
		
			void unbindDrawable(std::string);
		
			void clear(); /* Clears the window completely.*/
		
			void update(); // Updates every drawable.
		
			void render(); // Renders every drawable into the renderBuffer.
			
			void print(); // Renders the renderBuffer into the window.
		
		private:	
			unsigned int width, height;
			std::vector<std::pair<std::string, Drawable*> > drawables;
			std::vector<PixelData> renderBuffer;
			/* This vector consists of characters to draw and the color to be used. */
	};
}
#endif
