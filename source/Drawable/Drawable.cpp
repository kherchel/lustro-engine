#include "Drawable.hpp"

namespace lustro
{
	Drawable::Drawable() : x(0), y(0), width(0), height(0), depth(0) {}
	
	void Drawable::setPosition(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	
	void Drawable::setDepth(int depth)
	{
		this->depth = depth;
	}
	
	void Drawable::setSize(int width, int height)
	{
		this->width = width;
		this->height = height;
		buffer.clear();
		buffer.resize(width*height);
		zBuffer.clear();
		zBuffer.resize(width*height);
	}
	
	void Drawable::setPixel(int x, int y, PixelData tgPixelData)
	{
		if(x+y*width > buffer.size() || x+y*width < 0) return;
		buffer[x+y*width] = tgPixelData;
	}
	
	int Drawable::getX() const
	{
		return x;
	}
	
	int Drawable::getY() const
	{
		return y;
	}
	
	int Drawable::getDepth() const
	{
		return depth;
	}
	
	const std::vector<double>& Drawable::getZBuffer() const
	{
		return zBuffer;
	}
	
	const std::vector<PixelData>& Drawable::getBuffer() const
	{
		return buffer;
	}
	
	int Drawable::getWidth() const
	{
		return width;
	}
	
	int Drawable::getHeight() const
	{
		return height;
	}
	
	PixelData Drawable::getPixel(int x, int y) const
	{
		if(x < 0 || x >= width || y < 0 || y >= height) return PixelData();
		return buffer[x+y*width];
	}
	
	double Drawable::getZ(int x, int y) const
	{
		if(x < 0 || x >= width || y < 0 || y >= height) return 0;
		return zBuffer[x+y*width];
	}
	
	void Drawable::clear(PixelData pixel, int x1, int y1, int x2, int y2)
	{
		if(x2 == -1) x2 = width - x1;
		if(y2 == -1) y2 = height - y1;
		
		double infinity = std::numeric_limits<double>::infinity();
		
		for(int i = x1; i < x2; i++)
		{
			for(int j = y1; j < y2; j++)
			{
				buffer[i+j*width] = pixel;
				zBuffer[i+j*width] = infinity;
			}
		}
	}
	
}
