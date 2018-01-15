#include "Wall.hpp"

namespace lustro
{
	const long double Wall::epsilon = 0.0001;

	Wall::Wall() : x1(0), y1(0), x2(0), y2(0), collidable(true), looping(true), isActive(true), A(0), B(0), C(0), cachedSqrt(0), length(0) {}
	
	Wall::Wall(long double x1, long double y1, long double x2, long double y2, Texture* texture, bool collidable, bool looping, bool isActive)
		: x1(x1), y1(y1), x2(x2), y2(y2), texture(texture), collidable(collidable), looping(looping), isActive(isActive)
	{
		if(x1 - x2 == 0)
		{
			A = 1;
			B = 0;
			C = -x1;
		}
		else if(y1 - y2 == 0)
		{
			A = 0;
			B = 1;
			C = -y1;
		}
		else
		{
			A = (y1 - y2) / (x1 - x2);
			B = -1;
			C = y1 - A*x1;
		}
		cachedSqrt = sqrt(A * A + B * B);
		length = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	}
	
	
	
	long double Wall::getA() const
	{
		return A;
	}
	
	long double Wall::getB() const
	{
		return B;
	}
	
	long double Wall::getC() const
	{
		return C;
	}
	
	long double Wall::getSqrt() const
	{
		return cachedSqrt;
	}

	long double Wall::getLength() const
	{
		return length;
	}	
	
	long double Wall::getX1() const
	{
		return x1;
	}

	long double Wall::getY1() const
	{
		return y1;
	}	
	
	long double Wall::getX2() const
	{
		return x2;
	}

	long double Wall::getY2() const
	{
		return y2;
	}	
	
	Texture* Wall::getTexture()
	{
		return texture;
	}
	
	void Wall::setTexture(Texture* texture)
	{
		this->texture = texture;
	}
	
	void Wall::setName(std::string name)
	{
		this->name = name;
	}
	
	void Wall::setActivityState(bool state)
	{
		isActive = state;
	}
	
	bool Wall::getActivityState() const
	{
		return isActive;
	}
	
	bool Wall::isCollidable() const
	{
		return isActive && collidable;
	}
	
	bool Wall::isLooping() const
	{
		return looping;
	}
	
	std::string Wall::getName() const
	{
		return name;
	}
	
	PixelData Wall::getPixel(double xP, double yP, double partOfHeight) const
	{
		if(!isActive) return PixelData();
		if(!looping) return texture->getPixelRel(getPointOnTexturePosition(xP, yP), partOfHeight);
		return texture->getPixelRel(sqrt((xP-x1)*(xP-x1)+(yP-y1)*(yP-y1)), partOfHeight);
	}
	
	long double Wall::getPointOnTexturePosition(double x, double y) const
	{
		return sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1))/(length);
	}
	
	bool Wall::isPointOnWall(double x, double y, double difeps) const
	{
		if(difeps == -1)difeps = epsilon;
		if(!isActive) return false;
		if(fabs(A*x+B*y+C) > difeps) return false;
		return fabs(sqrt((x1-x)*(x1-x) + (y1-y)*(y1-y)) + sqrt((x2-x)*(x2-x) + (y2-y)*(y2-y)) - length) < difeps; 
	}
	
	std::string Wall::applyCollision(double& x, double& y, double oldX, double oldY, double collisionPointX, double collisionPointY)
	{
		const double translation = 0.01;
		double secA, secB, secC;

		secA = -B;
		secB = A;
		secC = B*x - A*y;
		
		double meetWG = A*secB - B*secA;
		double xP = (B*secC - C*secB)/meetWG, yP = (C*secA - A*secC)/meetWG;
		double xD1, xD2, yD1, yD2;
		if(secB == 0)
		{
			xD1 = xD2 = xP;
			yD1 = yP - translation;
			yD2 = yP + translation;
		}
		else if(secA == 0)
		{
			xD1 = xP - translation;
			xD2 = xP + translation;
			yD1 = yD2 = yP;
		}
		else
		{
			double translC1 = translation*cachedSqrt + C, 
				translC2 = - translation*cachedSqrt + C;
			xD1 = (B*secC - translC1*secB)/meetWG;
			xD2 = (B*secC - translC2*secB)/meetWG;
			yD1 = (translC1*secA - A*secC)/meetWG;
			yD2 = (translC2*secA - A*secC)/meetWG;
		}
		if((oldX-xD1)*(oldX-xD1)+(oldY-yD1)*(oldY-yD1) < (oldX-xD2)*(oldX-xD2)+(oldY-yD2)*(oldY-yD2))
		{	
			x = xD1;
			y = yD1;
		}
		else
		{
			x = xD2;
			y = yD2;
		}
		if(fabs(x*A+y*B+C)/cachedSqrt < translation-epsilon)napms(10000);
		return "";
	}		
}
