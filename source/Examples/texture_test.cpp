#include "../Texture/Texture.hpp"

int main()
{
	setlocale(LC_ALL, "");
	initscr();
	start_color();
	lustro::PixelData::initalizePixelDataPairs();
	lustro::Texture texture(10, 5);
	
	for(unsigned int i = 0; i != 5; i++)
		texture.copy(lustro::Texture(10, 1, lustro::PixelData(i, COLOR_GREEN, COLOR_BLUE)), 0, i);
	
	for(unsigned int i = 0; i != texture.getHeight(); i++)
	{
		for(unsigned int j = 0; j != texture.getWidth(); j++)
		{
			attron(COLOR_PAIR(texture.getPixelData(j, i).getPair()));
			printw(texture.getPixelData(j, i).getSymbol().c_str());
		}	
		printw("\n");
	}
		
	
	refresh();
	getch();
	endwin();
	return 0;
}
