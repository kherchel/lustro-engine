#include "../Wall.hpp"
#include "../../Drawable/Raycaster/Raycaster.hpp"
#include "../../Drawable/Spritecaster/Spritecaster.hpp"
#ifndef LINKEDWALL_HPP
#define LINKEDWALL_HPP


namespace lustro
{
	class Map;

	class LinkedWall : public Wall
	{
		public:
			LinkedWall();
			LinkedWall(long double, long double, long double, long double, Texture*, bool collidable = true, bool looping = true);
		
			void link(Map* map, LinkedWall* wall);
			
			void setCamera(double camX, double camY, double camRot) override;
			void setPixelCoords(unsigned int x, unsigned int y) override;
			std::string applyCollision(double& x, double& y, double oldX, double oldY, double collisionPointX, double collisionPointY); 
			
			bool isLinked() const;
			
			void postprocess(std::vector<PixelData>& buffer, std::vector<double>& zBuffer, 
				unsigned int width, unsigned int height, double pixelRatio, double fov);
			
			PixelData getPixel(double xP, double yP, double partOfHeight) const override;

		private:
			Map* map;
			std::string mapName;
			LinkedWall* linked;
			int minX, minY, maxX, maxY;
			double x1Dest, x2Dest, y1Dest, y2Dest;
			
			static unsigned int renderDepth;
			const static unsigned int maxRenderDepth = 9;
			std::vector<std::vector<std::pair<unsigned int, unsigned int>>> pixels;
			double cameraX, cameraY, cameraRot;
			
			
	};
	
}

#endif
