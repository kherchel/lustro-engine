#include "../Drawable.hpp"
#include "../../Wall/Wall.hpp"
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>
#include <limits>

#ifndef RAYCASTER_HPP
#define RAYCASTER_HPP

namespace lustro
{

	class Raycaster : public Drawable
	{
		public:
			Raycaster();
			Raycaster(double, double);
			
			void setFov(double);
			void setPixelRatio(double);
			void setSize(int, int);	
			
			double getFov() const;
			double getPixelRatio() const;
			
			void render() override;
			void update() override;
			
			void setCameraPosition(double, double);
			void setCameraRotation(double);
			
			double getCameraX() const;
			double getCameraY() const;
			double getCameraRotation() const;
			
			void setSkyColor(PixelData);
			void setGroundColor(PixelData);
			
			void raycast(const std::vector<Wall*>& walls, int firstLine = 0, int scanWidth = -1,
		 	int firstHorLine = 0, int scanHeight = -1, Wall* wallToOmit = nullptr);
			
		private:
			double fov, pixelRatio;
			double cameraX, cameraY, cameraRot;
			PixelData sky, ground;
			
	};
	
}

#endif
