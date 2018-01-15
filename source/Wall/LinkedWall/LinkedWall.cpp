#include "../../Map/Map.hpp"
#include "../Wall.hpp"

namespace lustro
{
	unsigned int LinkedWall::renderDepth = 0;

	LinkedWall::LinkedWall()
		: Wall(), map(nullptr), x1Dest(0), x2Dest(0), y1Dest(0), y2Dest(0), 
		cameraX(0), cameraY(0), cameraRot(0), minX(-1), maxX(-1), minY(-1), maxY(-1) 
	{
		pixels.resize(maxRenderDepth+1);
	}

	LinkedWall::LinkedWall(long double x1, long double x2, long double y1, long double y2, Texture* texture, bool collidable, bool looping)
		: Wall(x1, x2, y1, y2, texture, collidable, looping), map(nullptr), x1Dest(0), x2Dest(0), y1Dest(0), y2Dest(0), 
		cameraX(0), cameraY(0), cameraRot(0), minX(-1), maxX(-1), minY(-1), maxY(-1) 
	{
		pixels.resize(maxRenderDepth+1);	
	}
		
	void LinkedWall::link(Map* map, LinkedWall* second)
	{
		this->map = map;
		this->linked = second;
		
		x1Dest = second->x1;
		x2Dest = second->x2;
		y1Dest = second->y1;
		y2Dest = second->y2;
		
	}

	void LinkedWall::setPixelCoords(unsigned int x, unsigned int y)
	{
		if(renderDepth >= maxRenderDepth) return;
		pixels[renderDepth].push_back(std::pair<unsigned int, unsigned int>(x, y));
		if(minX == -1)
		{
			minX = maxX = x;
			minY = maxY = y;
			return;
		}
		minX = std::min(minX, (int)x);
		minY = std::min(minY, (int)y);
		
		maxX = std::max(maxX, (int)x);
		maxY = std::max(maxY, (int)y);
	}
	
	void LinkedWall::setCamera(double camX, double camY, double camRot)
	{
		cameraX = camX;
		cameraY = camY;
		cameraRot = camRot;
	}

	
	bool LinkedWall::isLinked() const
	{
		return map != nullptr;
	}
	
	PixelData LinkedWall::getPixel(double xP, double yP, double partOfHeight) const
	{
		if(isActive == false) return PixelData();
		return PixelData(1, COLOR_RED, COLOR_MAGENTA);
	}

	void LinkedWall::postprocess(std::vector<PixelData>& buffer, std::vector<double>& zBuffer, 
		unsigned int width, unsigned int height, double pixelRatio, double fov)
	{
	
		if(isActive == false || map == nullptr || pixels[renderDepth].size() == 0 || renderDepth >= maxRenderDepth) return;
		
		if(renderDepth == maxRenderDepth-1)
		{
			double infinity = std::numeric_limits<double>::infinity();
			for(auto& i : pixels[renderDepth])
			{
				buffer[i.first + i.second*width] = PixelData();
				zBuffer[i.first + i.second*width] = infinity;
			}	
			return;
		}
		int minXC = minX, maxXC = maxX, minYC = minY, maxYC = maxY;

		Raycaster raycaster;
		Spritecaster spritecaster;
		
		raycaster.setSize(width, height);
		spritecaster.setSize(width, height);
		
		raycaster.setCameraPosition(cameraX + x1Dest - x1, cameraY + y1Dest - y1);
		raycaster.setCameraRotation(cameraRot);
		raycaster.setFov(fov);
		raycaster.setGroundColor(map->getGroundColor());
		raycaster.setSkyColor(map->getSkyColor());
		raycaster.setPixelRatio(pixelRatio);
		
		minX = maxX = minY = maxY = -1;
		
		renderDepth++;
		raycaster.raycast(map->getWalls(), minXC, maxXC - minXC + 1,
											minYC, maxYC - minYC + 1, linked);
											
		//spritecaster.spritecast(map->getSprites(), raycaster);
		
		map->getSkybox()->setSize(raycaster.getWidth(), raycaster.getHeight());
		map->getSkybox()->setMode(3);
		map->getSkybox()->setDepth(std::numeric_limits<double>::infinity());
		
		if(map->getSkybox()->getTexture() != nullptr)
			map->getSkybox()->setShift(cameraX/360*map->getSkybox()->getTexture()->getWidth(),0);
		
		map->getSkybox()->update();
				
		renderDepth--;
										
		for(auto& i : pixels[renderDepth])
		{
			if(!spritecaster.getPixel(i.first, i.second).isTransparent())
			{
				buffer[i.first + i.second*width] = spritecaster.getPixel(i.first, i.second);
				zBuffer[i.first + i.second*width] = spritecaster.getZ(i.first, i.second);
			}
			else
			{ 			
				if(!raycaster.getPixel(i.first, i.second).isTransparent())
				{
					buffer[i.first + i.second*width] = raycaster.getPixel(i.first, i.second);
					zBuffer[i.first + i.second*width] = raycaster.getZ(i.first, i.second);
				}
				else
				{
					buffer[i.first + i.second*width] = map->getSkybox()->getPixel(i.first, i.second);
					zBuffer[i.first + i.second*width] = map->getSkybox()->getZ(i.first, i.second);
				}
			}
		}
		pixels[renderDepth].clear();
		pixels[renderDepth].reserve(1024);
		minX = maxX = minY = maxY = -1;
	}
	
	std::string LinkedWall::applyCollision(double& x, double& y, double oldX, double oldY, double collisionPointX, double collisionPointY)
	{
		x = x1Dest-x1 + x;
		y = y1Dest-y1 + y;
		std::string newName = map->checkCollisions(x, y, x1Dest-x1+collisionPointX, y1Dest-y1+collisionPointY);
		if(newName == "") return map->getName();
		return newName;
	}
			
}

