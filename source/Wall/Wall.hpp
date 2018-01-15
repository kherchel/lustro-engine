#include "../Texture/Texture.hpp"
#include <cmath>


#ifndef WALL_HPP_DEFINED
#define WALL_HPP_DEFINED

namespace lustro
{
	class Wall
	{
		public:
			Wall();
			Wall(long double, long double, long double, long double, Texture*, bool collidable = true, bool looping = true, bool isActive = true);
			
			long double getA() const;
			long double getB() const;
			long double getC() const;
			long double getSqrt() const;
			long double getLength() const;
			long double getX1() const;
			long double getY1() const;
			long double getX2() const;
			long double getY2() const;
			void setName(std::string name);
			std::string getName() const;
			
			bool isPointOnWall(double x, double y, double difeps = -1) const; //Point must be on line made by wall's ends
			long double getPointOnTexturePosition(double x, double y) const;
			void setTexture(Texture* texture);
			Texture* getTexture();
			void setActivityState(bool state);
			bool getActivityState() const;	
			bool isCollidable() const;
			bool isLooping() const;
			
			virtual void setCamera(double camX, double camY, double camRot) {}
			virtual void setRay(double rayA, double rayB, double rayC, double rayRot) {}
			virtual void setPixelCoords(unsigned int x, unsigned int y) {}
			virtual void postprocess(std::vector<PixelData>& buffer, std::vector<double>& zBuffer, unsigned int width, unsigned int height, double pixelRatio, double fov) {}
			virtual std::string applyCollision(double& x, double& y,
					double oldX, double oldY, double collisionPointX, double collisionPointY); 
			virtual PixelData getPixel(double xP, double yP, double partOfHeight) const;
			
		protected:
			std::string name;
			long double x1, y1, x2, y2;
			long double A, B, C;
			Texture* texture;
			bool collidable, looping, isActive;
			long double cachedSqrt, length;
			static const long double epsilon;
			//Event* touchEvent, useEvent;
	};
	
}

#endif
