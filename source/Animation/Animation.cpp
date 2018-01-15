#include "Animation.hpp"

namespace lustro
{

	Animation::Animation() : currentFrame(0), framerate(0) {}
	
	Animation::Animation(double framerate) : currentFrame(0), framerate(framerate) {}
	
	void Animation::addFrame(Texture* texture)
	{
		textures.push_back(texture);
	}
	
	void Animation::setFramerate(double framerate)
	{
		this->framerate = framerate;
	}
	
	void Animation::update()
	{
		if(textures.size() == 0) return;
		currentFrame += Timer::getMillis("delta")/(1000/Timer::appFramerate);
		currentFrame = currentFrame - ((int)currentFrame/textures.size()*textures.size());
	}
	
	Texture* Animation::getCurrentTexture()
	{
		if(textures.size() == 0) return nullptr;//{printw("%d", (int) currentFrame); refresh(); napms(1000); return nullptr;}
		return textures[(int)currentFrame];
	}

}
