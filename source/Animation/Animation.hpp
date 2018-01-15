#include "../Texture/Texture.hpp"
#include "../Timer/Timer.hpp"
#include <vector>

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

namespace lustro
{
	class Animation
	{
		public:
			Animation();
			Animation(double framerate);
			void addFrame(Texture* texture);
			void setFramerate(double framerate);
			Texture* getCurrentTexture();
			void update();
		
		private:
			std::vector<Texture*> textures;
			double currentFrame, framerate;
	};
}

#endif
