#ifndef CANVAS_HPP_INCLUDED
#define CANVAS_HPP_INCLUDED

#include "../Drawable.hpp"
#include "../../Texture/Texture.hpp"

namespace lustro
{
	class Canvas : public Drawable
	{
		public:
			Canvas();
			Canvas(Texture*);
			
			void bindTexture(Texture*);
			Texture* getTexture();
			void setMode(unsigned int);
			void setShift(int, int);
			void shift(int, int);
			//void setScale(float);
			void update();
			void render();
			
		private:
			Texture* texture;
			unsigned int mode;
			/*
				0 - fill
				1 - tile
				2 - center
				3 - fill vertically, tile horizontally
				4 - fill horizontally, tile vertically
			*/
			int x, y;
			//float scale;
	};
}

#endif
