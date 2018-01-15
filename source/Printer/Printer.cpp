#include "Printer.hpp"

namespace lustro
{
	Printer::Printer() {}
	
	void Printer::addTextToTexture(Texture* texture, int x, int y, 
	std::string text, unsigned int textColor, unsigned int bgColor, bool wordWrap)
	{
		if(wordWrap)
		{
			for(int i = 0; i < text.length(); i++)
			{
				if(x+i >= texture->getWidth())
				{
					addTextToTexture(texture, x, y+1, text.substr(i+1, std::string::npos), textColor, bgColor, true);
					return;
				}
				else
				{
					if(text[i] == '\n')
					{
						addTextToTexture(texture, x, y+1, text.substr(i+1, std::string::npos), textColor, bgColor, true);
						return;
					}
					texture->setPixel(x+i, y, PixelData(std::string()+text[i], textColor, bgColor));
				}
			}
			return;
		}
		for(int i = 0; i < text.length(); i++)
		{
			if(text[i] == '\n')
			{
				addTextToTexture(texture, x, y+1, text.substr(i+1, std::string::npos), textColor, bgColor, false);
				return;
			}
			texture->setPixel(x+i, y, PixelData(std::string()+text[i], textColor, bgColor));
		}
	}
}
