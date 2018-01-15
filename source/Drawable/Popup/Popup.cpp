#include "Popup.hpp"

namespace lustro
{
	Popup::Popup() : Drawable(), textPosition(0), lines(0), borderSize(1) {}
	
	/*Popup::Popup(unsigned int x, unsigned int y, unsigned int width, unsigned height, std::string text, PixelData color)
		: x(x), y(y), width(width), height(height), text(text), color(color)
	{
		
	}*/
	
	void Popup::setText(std::string newText)
	{
		text = newText;
		lines = 1;
		for(auto& i : text)
			lines += (i == '\n');
		update();
	}
	
	void Popup::setColor(PixelData newColor)
	{
		color = newColor;
		render();
	}
	
	void Popup::setTextPosition(unsigned int newTextPosition)
	{
		textPosition = newTextPosition;
		render();
	}
	
	void Popup::setBorderSize(unsigned int newBorderSize)
	{
		borderSize = newBorderSize;
		render();
	}
	
	void Popup::render()
	{	
		Drawable::clear(color);
		int tx = 0, ty = 0;
		switch(textPosition)
		{
			default:
			case 0: // center
				tx = width/2-text.length()/2;
				ty = height/2-lines/2;
				break;
				
			case 1: // top
				tx = width/2-text.length()/2;
				ty = borderSize;
				break;
				
			case 2: // top right
				tx = width-borderSize-text.length();
				ty = borderSize;
				break;
				
			case 3: // right
				tx = width-borderSize-text.length();
				ty = height/2-lines/2;
				break;
				
			case 4: // bottom right
				tx = width-borderSize-text.length();
				ty = height-lines-borderSize;
				break;
			
			case 5: // bottom
				tx = width/2-text.length()/2;
				ty = height-lines-borderSize;
				break;
				
			case 6: // bottom left
				tx = borderSize;
				ty = height-lines-borderSize;
				break;
				
			case 7: // left
				tx = borderSize;
				ty = height/2-lines/2;
				break;
				
			case 8: // top left
				tx = borderSize;
				ty = borderSize;
				break;
		}
		
		int basetx = tx;
		
		for(int i = 0; i < text.length(); i++)
		{
			if(text[i] == '\n')
			{
				tx = basetx;
				ty++;
				continue;
			}
			if(tx < borderSize || tx >= width-borderSize || ty < borderSize || ty >= height-borderSize) continue;

			buffer[ty*width+tx] = PixelData(std::string("")+text[i], color.getRawPair().first, color.getRawPair().second);
			tx++;
		}
	}
	
	void Popup::update()
	{
		
	}
}
