#include "Canvas.hpp"

namespace lustro
{
	Canvas::Canvas() : Drawable()
	{
		texture = nullptr;
		mode = 0;
	}
	
	Canvas::Canvas(Texture* texture) : Drawable(), texture(texture), mode(0) {}
			
	void Canvas::bindTexture(Texture* texture)
	{
		this->texture = texture;
	}
	
	Texture* Canvas::getTexture()
	{
		return texture;
	}
	
	void Canvas::setMode(unsigned int mode)
	{
		this->mode = mode;
	}
	
	void Canvas::setShift(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	
	void Canvas::shift(int x, int y)
	{
		this->x += x;
		this->y += y;
	}
	
	/*void Canvas::setScale(float scale)
	{
		this->scale = scale;
	}*/
	
	void Canvas::update()
	{
		if(texture == nullptr) return;
		Drawable::clear();
		
		/*while(true)
		{
			erase();
			printw("TEX>>");
			printw(std::to_string(texture->getWidth()).c_str());
			printw("x");
			printw(std::to_string(texture->getHeight()).c_str());
			printw("<<XET");
			refresh();
		}*/
		
		if(mode == 2)
		{
			for(unsigned int i = 0; i < texture->getWidth(); i++)
			{
				for(unsigned int j = 0; j < texture->getHeight(); j++)
				{
					Drawable::setPixel(width/2-texture->getWidth()/2+i+x, 
					height/2-texture->getHeight()/2+j+y, 
					texture->getPixelData(i,j));
				}
			}
			return;
		}
		for(unsigned int i = 0; i < width; i++)
		{
			for(unsigned int j = 0; j < height; j++)
			{
				switch(mode)
				{
					case 0:
						Drawable::setPixel(i, j, texture->getPixelData(float(i)/width*texture->getWidth(),
						float(j)/height*texture->getHeight()));
						break;

					case 1:
						Drawable::setPixel(i, j, texture->getPixelData((i+x)%texture->getWidth(),
						(j+y)%texture->getHeight()));
						break;
						
					case 3:
						Drawable::setPixel(i, j, texture->getPixelData((i+x)%texture->getWidth(),
						float(j)/height*texture->getHeight()));
						break;
						
					case 4:
						Drawable::setPixel(i, j, texture->getPixelData(float(i)/width*texture->getWidth(),
						(j+y)%texture->getHeight()));
						break;
				}
			}
		}
	}
	
	void Canvas::render()
	{
		
	}
}
