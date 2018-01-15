#ifndef SPRITECASTER_HPP_INCLUDED
#define SPRITECASTER_HPP_INCLUDED

#include "../Drawable.hpp"
#include "../Raycaster/Raycaster.hpp"
#include "../../Sprite2D/Sprite2D.hpp"
#include <cmath>

namespace lustro
{
	class Spritecaster : public Drawable
	{
		public:
			Spritecaster();
			void spritecast(const std::vector<Sprite2D*>&, const Raycaster& raycaster);
			
			void update();
			void render();
	};
}

#endif
