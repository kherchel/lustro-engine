#include "Toast.hpp"

namespace lustro
{
	
	Toast::Toast() : text(""), color(0, COLOR_WHITE, COLOR_BLACK),
		inAnimationTime(1), onScreenTime(4), outAnimationTime(1) {}
		
	Toast::Toast(PixelData color, double inAnimationTime, double onScreenTime, double outAnimationTime)
		: text(""), color(color), inAnimationTime(inAnimationTime), onScreenTime(onScreenTime), outAnimationTime(1) {}

	void Toast::start(std::string text)
	{
		Timer::stop(this->text);
		this->text = text;
		if(this->text.length() > width) this->text = this->text.substr(0, width);
		Timer::start(this->text);
	}

	void Toast::update()
	{
		
	}
	
	void Toast::showText(int firstX)
	{
		int firstTextX = (width-text.length())/2;
		for(int i = firstX; i != width-firstX; i++)
		{
			for(int j = 0; j != height; j++)
				buffer[i+j*width] = color;
			
			if(firstTextX > i || firstTextX + text.length() <= i) continue;
			
			buffer[i+(height/2)*width] = PixelData(std::string("") + text[i-firstTextX], color.getRawPair().first, color.getRawPair().second); 
		}
	}
	
	void Toast::render()
	{
		if(this->text == "")return;
		clear();
		Timer::stop(this->text);
		double time = Timer::getSeconds(this->text);
		if(time < inAnimationTime)
			showText((1-time/inAnimationTime)*width/2.);
		
		else if(time < inAnimationTime + onScreenTime)
			showText(0);
		
		else if(time < inAnimationTime + onScreenTime + outAnimationTime)
			showText((time-inAnimationTime-onScreenTime)/outAnimationTime*width/2.);
			
		else
			this->text = "";

	}
}		
