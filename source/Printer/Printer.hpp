#include "../Texture/Texture.hpp"

#ifndef PRINTER_HPP_INCLUDED
#define PRINTER_HPP_INCLUDED

namespace lustro
{
	class Printer
	{
		private:
			Printer();
			
		public:
			static void addTextToTexture(Texture*, int, int, std::string, unsigned int, unsigned int, bool wordWrap=false);
			//static void addTextToTexture(Texture*, int, int, std::string, unsigned int, bool wordWrap=false);
			//static void addTextToTexture(Texture*, int, int, std::string, bool wordWrap=false);
			/*
				Usage:
				Texture, x, y, string, textColor, bgColor, useWordWrap?
			*/
	};
}

#endif
