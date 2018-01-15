#include "PixelData.hpp"

namespace lustro
{
	std::string PixelData::getUnicodeFromDensity(unsigned short int density)
	{
		return (density < 5)?densityToUnicodeTable[density]:densityToUnicodeTable[0];
	}
	
	unsigned short int PixelData::getDensityFromUnicode(std::string unicode)
	{
		for(unsigned int i = 0; i < 5; i++)
		{
			if(densityToUnicodeTable[i] == unicode) return i;
		}
		return 6;
	}

	std::string PixelData::densityToUnicodeTable[5] = {" ", "\u2591", "\u2592", "\u2593", "\u2588"};
	const unsigned short int PixelData::transparent = 8;
	
	PixelData::PixelData() 
		: textPixelData(PixelData::transparent), backgroundPixelData(PixelData::transparent), symbol(" ") {}

	PixelData::PixelData(std::string tgSymbol, unsigned short int tgTextPixelData, unsigned short int tgBackgroundPixelData) 
		: textPixelData(tgTextPixelData), backgroundPixelData(tgBackgroundPixelData), symbol(tgSymbol) {}
	
	PixelData::PixelData(unsigned short int tgDensity, unsigned short int tgTextPixelData, unsigned short int tgBackgroundPixelData)
		: PixelData(densityToUnicodeTable[tgDensity], tgTextPixelData, tgBackgroundPixelData) {}
	
	bool PixelData::operator==(PixelData second) const
	{
		return (symbol == second.symbol && textPixelData == second.textPixelData && backgroundPixelData == second.backgroundPixelData);
	}
	
	PixelData PixelData::operator+(PixelData second) const
	{
		PixelData ret = *this;
	
		ret += second;
	
		return ret;
	}

	PixelData& PixelData::operator+=(PixelData second)
	{
		if(second.textPixelData != PixelData::transparent)	
		{
			textPixelData = second.textPixelData;
			symbol = second.symbol;
		}
		
		if(second.backgroundPixelData != PixelData::transparent)
			backgroundPixelData = second.backgroundPixelData;
		
		return *this;
	}

	unsigned short int PixelData::getPair() const
	{
		unsigned short int ret = 1;
		if(backgroundPixelData < 8) ret += backgroundPixelData*8;
		if(textPixelData < 8) ret += textPixelData;
		return ret;
	}
	
	std::pair<unsigned short int, unsigned short int> PixelData::getRawPair() const
	{
		return std::pair<unsigned short int, unsigned short int>(textPixelData, backgroundPixelData);
	}

	std::string PixelData::getSymbol() const
	{
		if(isTransparent()) return " ";
		return symbol;
	}

	bool PixelData::isTransparent() const
	{
		return textPixelData == transparent && backgroundPixelData == transparent;
	}
}
