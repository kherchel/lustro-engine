#include "Texture.hpp"

namespace lustro
{
	Texture::Texture() 
		: sizeX(0), sizeY(0) {}
	

	Texture::Texture(unsigned int sizeX, unsigned int sizeY)
		: sizeX(sizeX), sizeY(sizeY) 
	{
		data.resize(sizeX*sizeY);
	}

		
	Texture::Texture(unsigned int sizeX, unsigned int sizeY, PixelData defaultPixelData)
		: Texture(sizeX, sizeY)
	{
		for(auto& i : data)
			i = defaultPixelData;
	}
	
	Texture::Texture(unsigned int sizeX, unsigned int sizeY, std::string filename)
		: Texture(sizeX, sizeY)
	{
		data.clear();
		std::ifstream file(filename);
		for(size_t i = 0; i < sizeX*sizeY; i++)
		{
			if(file.eof()) return;
			std::string targetPixelData;
			
			file >> targetPixelData;
			if(targetPixelData[0] == '\\')
			{
				std::string symbol;
				if(targetPixelData[1] == '\\') symbol = '\\';
				else symbol = PixelData::getUnicodeFromDensity(targetPixelData[1]-'0');
				data.push_back(PixelData(symbol, targetPixelData[2]-'0', targetPixelData[3]-'0'));
			}
			else data.push_back(PixelData(std::string()+targetPixelData[0],targetPixelData[1]-'0',targetPixelData[2]-'0'));
		}
	}
	
	void Texture::setPixel(unsigned int x, unsigned int y, PixelData tgPixelData)
	{
		if(x+y*getWidth() >= data.size()) return;
		data[x+y*getWidth()] = tgPixelData;
	}

	PixelData Texture::getPixelData(unsigned int x, unsigned int y) const
	{
		if(x < 0 || y < 0 || x >= sizeX || y >= sizeY) return PixelData();
		return data[(int)x + (int)y * sizeX];	
	}
	
	PixelData Texture::getPixelRel(double x, double y) const
	{
		while(x < 0)x++;
		while(y < 0)y++;
		return getPixelData((x-(int)x)*sizeX, (y-(int)y)*sizeY);
	}
	
	unsigned int Texture::getWidth() const
	{
		return sizeX;
	}
	
	unsigned int Texture::getHeight() const
	{
		return sizeY;
	}

	void Texture::copy(Texture second, unsigned int tgX, unsigned int tgY)
	{
		unsigned int cpSizeX = std::min(sizeX - tgX, second.sizeX), cpSizeY = std::min(sizeY - tgY, second.sizeY);
		for(unsigned int i = 0; i != cpSizeX; i++)
			for(unsigned int j = 0; j != cpSizeY; j++)
				data[i + tgX + (j + tgY) * sizeX] = second.getPixelData(i, j);
	}
	
	void Texture::copyFragment(Texture second, unsigned int srcX, unsigned int srcY, 
				unsigned int tgX, unsigned int tgY, unsigned int tgWidth, unsigned int tgHeight)
	{
		unsigned int cpSizeX = std::min(second.sizeX - srcX, std::min(tgWidth, sizeX - tgX)),
			cpSizeY = std::min(second.sizeY - srcY, std::min(tgHeight, sizeY - tgY));
			
		for(unsigned int i = 0; i != cpSizeX; i++)
			for(unsigned int j = 0; j != cpSizeY; j++)
				data[i + tgX + (j + tgY) * sizeX] = second.getPixelData(i + srcX, j + srcY);
	}
}
