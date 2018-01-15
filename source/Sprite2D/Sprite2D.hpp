#ifndef SPRITE2D_HPP_INCLUDED
#define SPRITE2D_HPP_INCLUDED

#include "../Texture/Texture.hpp"

namespace lustro
{
	class Sprite2D
	{
		public:
			Sprite2D();
			Sprite2D(Texture*);
			Sprite2D(Texture*, double, double);
			
			void setPosition(double, double);
			void setTexture(Texture* texture);
			void setActivityState(bool);
			bool getActivityState() const;
			const Texture& getTexture() const;
			double getX() const;
			double getY() const;
			PixelData getPixel(double, double) const;
		
		private:
			Texture *texture;
			bool isActive;
			double x, y;
			
	};
}

#endif
