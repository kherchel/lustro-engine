#include <ncurses.h>
#include <string>

#ifndef PixelData_HPP
#define PixelData_HPP

namespace lustro
{
	class PixelData
	{
	public:
		static bool initalizePixelDataPairs()
		{
			if(!has_colors()) return false;
			for(unsigned short int i = 0; i < 64; i++)
			{
				init_pair(i + 1, i/8, i%8);
			}
			return true;
		}
		static std::string getUnicodeFromDensity(unsigned short int);
		static unsigned short int getDensityFromUnicode(std::string);
		static const unsigned short int transparent;
			
		PixelData();
		PixelData(std::string tgSymbol, unsigned short int tgTextPixelData, unsigned short int tgBackgroundPixelData);
		PixelData(unsigned short int, unsigned short int, unsigned short int);
		
		bool operator==(PixelData second) const;
		PixelData operator+(PixelData second) const;
		PixelData& operator+=(PixelData second);
		
		std::string getSymbol() const;
		unsigned short int getPair() const;
		std::pair<unsigned short int, unsigned short int> getRawPair() const;
		bool isTransparent() const;
		
	private:
		static std::string densityToUnicodeTable[5];
	
		unsigned short int textPixelData, backgroundPixelData; 
		std::string symbol;
	};

}

#endif
