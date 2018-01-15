#include <string>
#include <fstream>
#include <vector>
#include "../PixelData/PixelData.hpp"

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

namespace lustro
{

	class Texture
	{
		public:
			Texture();
			Texture(unsigned int sizeX, unsigned int sizeY);
			Texture(unsigned int, unsigned int, std::string);
			Texture(unsigned int sizeX, unsigned int sizeY, PixelData defaultPixelData);
			Texture(std::string filename);
			bool loadFromFile(std::string filename);
			
			PixelData getPixelData(unsigned int x, unsigned int y) const;
			PixelData getPixelRel(double x, double y) const;
			unsigned int getWidth() const;
			unsigned int getHeight() const;
			
			void setPixel(unsigned int x, unsigned int y, PixelData tgPixelData);
			void copy(Texture second, unsigned int tgX, unsigned int tgY);
			void copyFragment(Texture second, unsigned int srcX, unsigned int srcY, 
				unsigned int tgX, unsigned int tgY, unsigned int tgWidth, unsigned int tgHeight);
			
		private:
			unsigned int sizeX, sizeY;
			std::vector<PixelData> data;
	};
	
}

#endif
