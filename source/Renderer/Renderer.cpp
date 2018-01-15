#include "Renderer.hpp"

namespace lustro
{
	Renderer::Renderer() {}
	
	Renderer::Renderer(unsigned int width, unsigned int height)
		: width(width), height(height)
	{
		renderBuffer.resize(width*height);
	}
	
	void Renderer::bindDrawable(Drawable* targetDrawable, std::string name)
	{
		for(auto& i : drawables)
		{
			if(i.first == name)
			{
				i.second = targetDrawable;
				return;
			}
		}
		drawables.push_back(std::pair<std::string, Drawable*>(name, targetDrawable));	
	}
	
	void Renderer::unbindDrawable(std::string name)
	{
		for(unsigned int i = 0; i < drawables.size(); i++)
		{
			if(drawables[i].first == name) drawables.erase(drawables.begin()+i);
		}
	}
	
	void Renderer::clear()
	{
		for(auto& i : renderBuffer)
		{
			i = PixelData();
		}
	}
	
	void Renderer::update()
	{
		for(auto& i : drawables)
		{
			i.second->update();
		}
		std::sort(drawables.begin(), drawables.end(), [](auto a, auto b)->bool{return a.second->getDepth() < b.second->getDepth();});
	}
	
	void Renderer::render()
	{
		clear();
		for(auto& i : drawables)
		{
			i.second->render();
			for(auto x = 0; x < i.second->getWidth(); x++)
			{
				for(auto y = 0; y < i.second->getHeight(); y++)
				{
					if(i.second->getX()+x >= width || i.second->getY()+y >= height) continue;
				
					if(!i.second->getPixel(x, y).isTransparent())
					{
						renderBuffer[i.second->getX()+x+y*width+i.second->getY()*width] = i.second->getPixel(x, y);
					}
				}
			}
		}
	}
	
	void Renderer::print()
	{
		
		unsigned int n = 0;
		
		if(false)
		{
			erase();
			for(auto& i : renderBuffer)
			{
				if(n%width == 0 && n != 0) printw("\n");
		
				attron(COLOR_PAIR(i.getPair()));
				printw(i.getSymbol().c_str());
				n++;
			}
		}
		else
		{
			erase();
			std::vector<unsigned int> pixels[65];	
			
			for(unsigned int n = 0; n != width*height; n++)
			{
				if(pixels[renderBuffer[n].getPair()].size() == 0)pixels[renderBuffer[n].getPair()].reserve(width*height/8);
				pixels[renderBuffer[n].getPair()].push_back(n);
			}
			
			for(unsigned int n = 0; n != 65; n++)
			{
				if(pixels[n].size() == 0) continue;
				attron(COLOR_PAIR(n));
				for(auto& i : pixels[n])
					mvprintw(i/width, i%width, renderBuffer[i].getSymbol().c_str());	
			}
		}
		refresh();
	}
}
