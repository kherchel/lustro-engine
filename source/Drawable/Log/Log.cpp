#include "Log.hpp"

namespace lustro
{	
	Log::Log() : color(0, COLOR_WHITE, COLOR_BLACK) {}

	Log::Log(PixelData color) : color(color) {}
	
	void Log::addMessage(std::string message)
	{
		messages.push_back(message);
	}
	
	void Log::update() {}
	
	void Log::render()
	{
		int textHeight = 0;
		std::string combined = "";
		for(int i = 0; i != messages.size(); i++)
		{
			int lastCopied = 0, lastCheckpoint = 0, fragmentLength = 0;
			std::string messageTransformed = "";
			for(int j = 0; j != messages[i].length(); j++)
			{
				if(messages[i][j] == ' ')lastCheckpoint = j;
				fragmentLength++;
				if(fragmentLength >= width - 2)
				{
					j = lastCheckpoint;
					messageTransformed += messages[i].substr(lastCopied, lastCheckpoint-lastCopied) + '\n';
					lastCopied = lastCheckpoint;
					fragmentLength = 0;
					textHeight++;
				}
				else if(j == messages[i].length() - 1)
				{
					messageTransformed += messages[i].substr(lastCopied, j-lastCopied+1);
				}
				 
			}
			combined += "> " + messageTransformed;
			textHeight++;
			if(i != messages.size()-1) {combined += '\n';}
		}
		
		clear(color);
		int currentColumn = 0;
		int currentRow = -textHeight+height-1;
		for(int i = 0; i != combined.length(); i++)
		{
			if(combined[i] == '\n') {currentColumn = 0; currentRow++; continue;}
			if(currentRow <= 0) continue;
			buffer[(currentColumn+1) + ((currentRow))*width] = 
				PixelData(std::string("") + combined[i], color.getRawPair().first, color.getRawPair().second);
			
			currentColumn++;
		}
	}
}
