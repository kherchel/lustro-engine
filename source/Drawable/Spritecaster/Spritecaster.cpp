#include "Spritecaster.hpp"

namespace lustro
{
	Spritecaster::Spritecaster() {}
	
	void Spritecaster::spritecast(const std::vector<Sprite2D*>& sprites, const Raycaster& raycaster)
	{
		Drawable::clear();
		double infinity = std::numeric_limits<double>::infinity();
	
		for(auto& i : sprites)
		{
			if(i == nullptr)continue;
			if(!i->getActivityState()) continue;
			float distanceTo = (sqrt(pow(i->getY() - raycaster.getCameraY() , 2) + pow(i->getX() - raycaster.getCameraX(), 2)));
			float scale = 3./2/distanceTo;
			
			float targetAngle = atan2(i->getY() - raycaster.getCameraY(), i->getX() - raycaster.getCameraX())/M_PI*180 - raycaster.getCameraRotation() + 90;
			targetAngle = float(int(targetAngle)%360) + float(targetAngle-int(targetAngle));

			while(targetAngle < -raycaster.getFov()/2) targetAngle += 360; 
			int targetX = getWidth()/raycaster.getFov()*(targetAngle+raycaster.getFov()/2);
			int targetY = getHeight()/2;
			
			for(int tx = targetX - scale*i->getTexture().getWidth()/2; tx < targetX + (int)(scale*i->getTexture().getWidth()/2); tx++)
			{
				if(tx < 0 || tx >= getWidth()) continue;
				
				for(int ty = getHeight()/2-scale*i->getTexture().getHeight()/2; ty < (int)(getHeight()/2+scale*i->getTexture().getHeight()/2); ty++)
				{
					if(ty < 0 || ty >= getHeight()) continue;
					
					unsigned int bX = (tx-(targetX-scale*i->getTexture().getWidth()/2))/(targetX + scale*i->getTexture().getWidth()/2);
					unsigned int bY = (ty-(targetY-scale*i->getTexture().getHeight()/2))/(targetY + scale*i->getTexture().getHeight()/2);
					if(i->getPixel(bX, bY).isTransparent()) continue;
					if(raycaster.getZ(tx, ty) > distanceTo*distanceTo)
					{
						buffer[tx+ty*getWidth()] = i->getPixel(bX, bY);
						zBuffer[tx+ty*getWidth()] = distanceTo*distanceTo;
					}
				}
			}
		}
	}
	
	void Spritecaster::update() {}
	void Spritecaster::render() {}
}
