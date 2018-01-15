#include "Raycaster.hpp"

namespace lustro
{
	
	Raycaster::Raycaster()
		: Drawable(), fov(90), pixelRatio(5./8.), cameraX(0), cameraY(0), cameraRot(0) {}
		
	Raycaster::Raycaster(double fov, double pixelRatio)
		: Drawable(), fov(fov), pixelRatio(pixelRatio), cameraX(0), cameraY(0), cameraRot(0) {}
		
	void Raycaster::setFov(double fov)
	{
		this->fov = fov;
	}
	
	double Raycaster::getFov() const
	{
		return fov;
	} 
	
	void Raycaster::setPixelRatio(double pixelRatio)
	{
		this->pixelRatio = pixelRatio;
	}
	
	double Raycaster::getPixelRatio() const
	{
		return pixelRatio;
	} 
	
	void Raycaster::setCameraPosition(double x, double y)
	{
		cameraX = x;
		cameraY = y;
	}
	
	double Raycaster::getCameraX() const
	{
		return cameraX;
	}
	
	double Raycaster::getCameraY() const
	{
		return cameraY;
	}
	
	void Raycaster::setCameraRotation(double rot)
	{
		cameraRot = rot;
	}
	
	double Raycaster::getCameraRotation() const
	{
		return cameraRot;
	}
	
	void Raycaster::setSize(int width, int height)
	{
		Drawable::setSize(width, height);
	}
	
	void Raycaster::setSkyColor(PixelData sky)
	{
		this->sky = sky;
	}

	void Raycaster::setGroundColor(PixelData ground)
	{
		this->ground = ground;
	}
	
	void Raycaster::update(){}
	
	void Raycaster::render(){}
	
	void Raycaster::raycast(const std::vector<Wall*>& walls, int firstLine, int scanWidth, int firstHorLine, int scanHeight, 
			Wall* wallToOmit)
	{
		if(scanWidth == -1) scanWidth = width;
		if(scanHeight == -1) scanHeight = height;
		
		int lastLine = std::min(firstLine + scanWidth, width),
			lastHorLine = std::min(height, firstHorLine + scanHeight);
		
		Drawable::clear(PixelData(), firstLine, firstHorLine, lastLine, lastHorLine);
		
		double cameraA, cameraB, cameraC, cameraSqrt, cameraDC;
		
		if(sin((cameraRot)*M_PI/180) == 0)
		{
			cameraA = 1;
			cameraB = 0;
			cameraC = -cameraX;
		}
		else if(cos((cameraRot)*M_PI/180) == 0)
		{
			cameraA = 0;
			cameraB = 1;
			cameraC = -cameraY;
		}
		else
		{
			cameraA = -1/tan((cameraRot)*M_PI/180);
			cameraB = -1;
			cameraC = cameraY - cameraA * cameraX;
		}
		
		cameraDC = cameraB*cameraX - cameraA*cameraY;
		cameraSqrt = sqrt(cameraA*cameraA + cameraB*cameraB);
		
		int half = (int)height/2;
		double precalculatedHeightRatio = 3*height/2.*pixelRatio;
		
		for(int currentLine = firstLine; currentLine < lastLine; currentLine++)
		{
			double rayRotDeg = (cameraRot + (currentLine - width/2) * fov / width);
			double rayRotRad = rayRotDeg * M_PI / 180;
			double rayCos = cos(rayRotRad), raySin = sin(rayRotRad);
			double rayA, rayB, rayC;
			
			if(raySin == 0)
			{
				rayA = 1;
				rayB = 0;
				rayC = -cameraX;
			}
			else if(rayCos == 0)
			{
				rayA = 0;
				rayB = 1;
				rayC = -cameraY;
			}
			else
			{
				rayA = -1./tan(rayRotRad);
				rayB = -1;
				rayC = cameraY - rayA * cameraX;
			}
			
			std::vector<std::pair<double, std::tuple<Wall*, double, double>>> points;
			for(auto& i : walls)
			{
				if(!(i->getActivityState())) continue;
				double wg = rayA*i->getB() - rayB*i->getA();
				if(wg == 0) {continue;}
				double x = (rayB*i->getC() - rayC*i->getB())/wg, y = (rayC*i->getA() - rayA*i->getC())/wg;
				if(!i->isPointOnWall(x, y)) continue;
				double rayLengthPow = (x-cameraX)*(x-cameraX) + (y-cameraY)*(y-cameraY);
				double tempSqrt = sqrt(rayLengthPow)/2;
				double tempX = cameraX + raySin*tempSqrt,
					tempY = cameraY - rayCos*tempSqrt;
				if((tempX-x)*(tempX-x)+(tempY-y)*(tempY-y) > rayLengthPow) continue;
				
				points.push_back(
					std::pair<double, std::tuple<Wall*, double, double>>(rayLengthPow, std::tuple<Wall*, double, double>(i, x, y)));
			}
			
			std::sort(points.begin(), points.end(), [](auto a, auto b)->bool{return a.first < b.first;});
			
			bool metWall = false;
			for(auto& i : points)
			{
				Wall* ptr = std::get<0>(i.second);
				double xP = std::get<1>(i.second), yP = std::get<2>(i.second);
				if(ptr == wallToOmit) {metWall = true; continue;}
				if(wallToOmit != nullptr && !metWall) continue;
				bool isTransparent = false;
				double persDist = fabs(-cameraB*xP + cameraA*yP + cameraDC)/cameraSqrt;
				
				int calculatedHeight = precalculatedHeightRatio/persDist;
				for(int j = 0; j != calculatedHeight*2; j++)
				{
					if(half + j - calculatedHeight < firstHorLine || half + j - calculatedHeight >= lastHorLine) continue;
					if(zBuffer[currentLine + (half+j-calculatedHeight)*width] <= i.first) continue; 
	
					ptr->setCamera(cameraX, cameraY, cameraRot);
					ptr->setRay(rayA, rayB, rayC, rayRotDeg);
					ptr->setPixelCoords(currentLine, half + j - calculatedHeight);
					
					PixelData newPixel = ptr->getPixel(xP, yP, (double)j/calculatedHeight/2);  
					
					if(newPixel.isTransparent())
					{
						isTransparent = true; 
						continue;
					}
					
					buffer[currentLine + (half+j-calculatedHeight)*width] = newPixel;
					zBuffer[currentLine + (half+j-calculatedHeight)*width] = i.first;
				}

				if(!isTransparent) break;			
			}
		}
		
		for(auto& i : walls)
		{
			if(!(i->getActivityState()) || wallToOmit == i) continue;
			i->postprocess(buffer, zBuffer, width, height, pixelRatio, fov);
		}
		
		/*for(int i = firstLine; i < lastLine; i++)
		{
			for(int j = firstHorLine; j < std::min(height/2, lastHorLine); j++)
	    	{
	    		if(buffer[i+j*width].isTransparent())
	    			buffer[i+j*width] = sky;
	    	}
	    	for(int j = height/2; j < lastHorLine; j++)
	    	{
	    		if(buffer[i+j*width].isTransparent())
	    			buffer[i+j*width] = ground;
	    	}
		}*/
	}
}
